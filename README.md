# Device Metrics

This is a tool to capture device metrics such as CPU usage, memory usage, and CPU temperature, written in C++.

Example usage:
```c++
DeviceMetrics device_metrics;
// Get CPU temperature
device_metrics.GetCPUTemperature()

// Get Per CPU usage
vector<float> usages = device_metrics.GetUsagePerCPU();
for (int  i = 0; i < usages.size(); i++)
{
	usages[i] // indicates i'th CPU usage as a percentage
}
```

To build `main.cc`:
```bash
mkdir build && cd build/ # create build director and cd 
cmake .. && make # build main.cc
./main # execute main
```

