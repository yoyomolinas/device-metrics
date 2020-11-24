# Device Metrics

This is a tool to capture device metrics such as CPU usage, memory usage, and CPU temperature, written in C++.

### Build
Run the following commands in console to build `main.cc` and execute
```bash
mkdir build && cd build/ # create build director and cd 
cmake .. && make # build main.cc
./main # execute main
```

### Example Usage
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

### Platform Compatibility
This code is compatible with `Linux` platforms and is tested on `RasbianOS`.


