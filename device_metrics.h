#ifndef DEVICE_STATUS_H_
#define DEVICE_STATUS_H_

#include <string>
#include <vector>

class DeviceMetrics
{
private:
    /** Number of states displayed for cpu when `cat /proc/stat` */
    const static int NUM_CPU_STATES = 10;

    /** 
         * Indices of CPU states read from /proc/stats.
         * Example usage: (CPUData)data.times[S_USER] */
    enum CPUState
    {
        S_USER,      // time spent in user mode.
        S_NICE,      // time spent in user mode with low priority.
        S_SYSTEM,    // time spent in system mode.
        S_IDLE,      // time spent in the idle task.
        S_IOWAIT,    // time waiting for I/O to complete.
        S_IRQ,       // time servicing hardware interrupts.
        S_SOFTIRQ,   // time servicing software interrupts.
        S_STEAL,     // time spent in other operating systems when running in a virtualized environment.
        S_GUEST,     // time spent running a virtual CPU for guest operating systems.
        S_GUEST_NICE // time spent running a low priority virtual CPU for guest operating systems.
    };

    /**
         * A container for CPU data.
         */
    typedef struct CPUData
    {
        std::string cpu;
        size_t times[NUM_CPU_STATES];
    } CPUData;

    /** 
         * Store current data to compute delta each time
         * GetUsagePerCPU or GetUsageCPU is called 
         */
    std::vector<CPUData> cur_data;

    /**
         * A function to read CPU statistics into a CPUData container.
         * @param entries a reference to a CPUData vector
         */
    void ReadStatsCPU(std::vector<CPUData> &entries);

    /** @return total idle time spent */
    float GetIdleTime(const CPUData &e);

    /** @return total active time spent */
    float GetActiveTime(const CPUData &e);

public:
    DeviceMetrics();
    /**
         * A function to read CPU temperature in degrees.
         * @return float temperature
         */
    float GetCPUTemperature();

    /**
         * A function to fetch percent CPU utiliazation for each core.
         * @return a vector of percent usage for each cpu
         * First element is average for all.
         */
    std::vector<float> GetUsagePerCPU();
};

#endif