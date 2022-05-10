#pragma once

#include "../entities/field.h"
#include "../../common/opencl.h"
#include <map>
#include <optional>

namespace GEng
{
class MainEngine
{
public:
    MainEngine(PField state, const cl::Device& device);
    const PField step(const int countSteps);
    PField getState();
    PCField getConstState()const;

    void setState(const PField &newPState);

private:
    bool buildProgram();


private:
    PField m_pState;

    cl::Device m_device;
    cl::Context m_context;
    std::optional<cl::CommandQueue> m_optQueue;
    cl::Program m_fluidProg;
    bool m_bfluidProg{false};

    std::map<int, cl::Buffer> m_mapBuffers;
    enum eBuffers
    {
        B_buffer = LT__END,
        B_flowRate,
        B_width,
        B_height,
        B_lenght,

        B__End
    };
};
}
