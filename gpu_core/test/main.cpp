#include <iostream>
#include "../engine/mainengine.h"
#include <chrono>

cl::Device getDevice()
{
    cl_int error = 0;
    std::vector<cl::Platform> all_platforms;
    error = cl::Platform::get(&all_platforms);
    if(error < 0)
    {
        std::cerr << "Unable to find any OpenCL platforms\n";
        exit(1);
    } else if (all_platforms.empty())
    {
        std::cerr << "Unable to find any device\n";
        exit(2);
    } else if (all_platforms.size() != 1)
    {
        std::cerr << "Warrning: count platforms are: " << all_platforms.size() << "\n";
        std::cerr << "Last celected: " << all_platforms.back().getInfo<CL_PLATFORM_NAME>() << "\n";
    }
    const auto& platform = all_platforms.back();
    std::vector<cl::Device> all_devices;
    error = platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (error != CL_SUCCESS )
    {
        std::cerr << "Unable to obtain any OpenCL compliant device info\n";
        exit(1);
    }
    if (all_devices.empty())
    {
        std::cerr << "Unable to obtain any OpenCL compliant device info/n";
        exit(1);
    }else if (all_devices.size() != 1)
    {
        std::cerr << "Warrning: count device are: " << all_devices.size() << "\n";
        std::cerr << "Last celected: " << all_devices.back().getInfo<CL_DEVICE_NAME>() << "\n";
    }

    return std::move(all_devices.back());
}


int main()
{
    const int width = 1000;
    const int height = 1000;
    constexpr int lenght = width * height;
    const int countIterations = 1000;

    GEng::PField pField(new GEng::Field(TSize(width,height), 0));
    GEng::MainEngine engine(pField, getDevice());


    auto t1 = std::chrono::high_resolution_clock::now();
    engine.step(countIterations);
    auto t2 = std::chrono::high_resolution_clock::now();

    long long duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    double CUPS = static_cast<long long>(lenght)*countIterations / duration;


    std::cout << "CUPS: " << CUPS << "M\n\n";
    return 0;
}
