#include "./device_metrics.h"

#include <fstream>
#include <sstream>
#include <cassert>

// constructor
DeviceMetrics::DeviceMetrics()
{
	std::vector<CPUData> entries;
	this->ReadStatsCPU(entries);
	this->cur_data = entries;
}

// Return cpu temperature in degrees
float DeviceMetrics::GetCPUTemperature()
{
	float deg, millideg;
	std::string fname = "/sys/class/thermal/thermal_zone0/temp"; // file where temperature is stored
	std::ifstream file_temp(fname);								 // open
	std::string line;
	std::getline(file_temp, line); // read millidegrees
	std::istringstream ln(line);   //make a stream for the line itself
	ln >> millideg;				   // cvt to float
	deg = millideg / 1000;		   // cvt to degrees
	return deg;
}

// read stats from file into entries
void DeviceMetrics::ReadStatsCPU(std::vector<CPUData> &entries)
{
	std::ifstream fileStat("/proc/stat");

	std::string line;

	const std::string STR_CPU("cpu");
	const std::size_t LEN_STR_CPU = STR_CPU.size();
	const std::string STR_TOT("tot");

	while (std::getline(fileStat, line))
	{
		// cpu stats line found
		if (!line.compare(0, LEN_STR_CPU, STR_CPU))
		{
			std::istringstream ss(line);

			// store entry
			entries.emplace_back(CPUData());
			CPUData &entry = entries.back();

			// read cpu label
			ss >> entry.cpu;

			if (entry.cpu.size() > LEN_STR_CPU)
				entry.cpu.erase(0, LEN_STR_CPU);
			else
				entry.cpu = STR_TOT;

			// read times
			for (int i = 0; i < NUM_CPU_STATES; ++i)
				ss >> entry.times[i];
		}
	}
}

// The total idle time is the sum of the fields idle and iowait
float DeviceMetrics::GetIdleTime(const CPUData &e)
{
	size_t time = e.times[S_IDLE] +
				  e.times[S_IOWAIT];
	return static_cast<float>(time);
}

// The active time is the sum of all the other fields:
float DeviceMetrics::GetActiveTime(const CPUData &e)
{
	size_t time = e.times[S_USER] +
				  e.times[S_NICE] +
				  e.times[S_SYSTEM] +
				  e.times[S_IRQ] +
				  e.times[S_SOFTIRQ] +
				  e.times[S_STEAL] +
				  e.times[S_GUEST] +
				  e.times[S_GUEST_NICE];
	return static_cast<float>(time);
}

std::vector<float> DeviceMetrics::GetUsagePerCPU()
{
	std::vector<float> ret;
	std::vector<CPUData> entries;
	this->ReadStatsCPU(entries);
	assert(entries.size() == this->cur_data.size());
	for (int i = 0; i < this->cur_data.size(); i++)
	{
		float cur_active_time = this->GetActiveTime(this->cur_data[i]);
		float cur_idle_time = this->GetIdleTime(this->cur_data[i]);
		float cur_total_time = cur_idle_time + cur_active_time;

		const float new_active_time = this->GetActiveTime(entries[i]);
		const float new_idle_time = this->GetIdleTime(entries[i]);
		const float new_total_time = new_idle_time + new_active_time;

		const float delta_active_time = new_active_time - cur_active_time;
		const float delta_idle_time = new_idle_time - cur_idle_time;
		const float delta_total_time = new_total_time - cur_total_time;
		const float percent_usage = delta_active_time / delta_total_time * 100;
		ret.push_back(percent_usage);
	}
	return ret;
}
