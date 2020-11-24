#include "./device_metrics.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    DeviceMetrics device_metrics;
    for (int i = 0; i < 100; i++)
    {
        cout << "CPU temperature: " << setprecision(3) << device_metrics.GetCPUTemperature() << endl;
        vector<float> usages = device_metrics.GetUsagePerCPU();
        for (int i = 0; i < usages.size(); i++)
        {
            cout << "CPU[" << i << "] " << setprecision(3)
                 << "Usage : " << usages[i] << "% ";
        }
    }
}