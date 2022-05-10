#include "mainengine.h"
#include <iostream>
#include <fstream>

using namespace GEng;

MainEngine::MainEngine(PField state, const cl::Device &device) :
    m_pState(state), m_device(device), m_context(device) {}

const PField MainEngine::step(const int countSteps)
{
    if (m_bfluidProg == false)
        if (buildProgram() == false)
            throw;

    const int bufLen = m_pState->size.length();
    const int width  = m_pState->size.w;
    const int height = m_pState->size.h;

    if (m_mapBuffers.size() < B__End)
    {
        m_mapBuffers.clear();
        int errBuffer;
        for (int i = 0; i < LT__END; i++)
        {
            cl::Buffer buffer(m_context, CL_MEM_READ_WRITE, sizeof(int) * bufLen, NULL, &errBuffer);
            if (errBuffer != CL_SUCCESS)
                throw ;
            m_mapBuffers.insert(std::make_pair(i, std::move(buffer)));
        }
        // buffer for swap
        m_mapBuffers.insert(std::make_pair(
                                B_buffer,
                                cl::Buffer(m_context, CL_MEM_READ_WRITE, sizeof(int) * bufLen)));
        // flow rate
        m_mapBuffers.insert(std::make_pair(
                                B_flowRate,
                                cl::Buffer(m_context, CL_MEM_READ_WRITE, sizeof(int))));
        // buffer size
        m_mapBuffers.insert(std::make_pair(
                                B_width,
                                cl::Buffer(m_context, CL_MEM_READ_WRITE, sizeof(int))));
        m_mapBuffers.insert(std::make_pair(
                                B_height,
                                cl::Buffer(m_context, CL_MEM_READ_WRITE, sizeof(int))));
        m_mapBuffers.insert(std::make_pair(
                                B_lenght,
                                cl::Buffer(m_context, CL_MEM_READ_WRITE, sizeof(int))));


        m_optQueue = cl::CommandQueue(m_context, m_device);
        for (int i = 0; i < LT__END; i++)
        {
            cl_int errQueue = m_optQueue->enqueueWriteBuffer(
                        m_mapBuffers[i], CL_TRUE, 0, sizeof(int) * bufLen, &m_pState->arrLiquids[i]);
            if (errQueue != CL_SUCCESS)
                throw ;
        }

        m_optQueue->enqueueWriteBuffer(
                    m_mapBuffers[B_width], CL_TRUE, 0, sizeof(int), &width);
        m_optQueue->enqueueWriteBuffer(
                    m_mapBuffers[B_height], CL_TRUE, 0, sizeof(int), &height);
        m_optQueue->enqueueWriteBuffer(
                    m_mapBuffers[B_lenght], CL_TRUE, 0, sizeof(int), &bufLen);
    }

    cl::Kernel calcFluids(m_fluidProg, "calcFluids");
    for (int step = 0; step < countSteps; step++)
        for (int i = 0; i < LT__END; i++)
        {
            m_optQueue->enqueueWriteBuffer(
                        m_mapBuffers[B_flowRate], CL_TRUE, 0, sizeof(int), &m_pState->arrLiquids.flowRate[i]);

            calcFluids.setArg(0, m_mapBuffers[i]);
            calcFluids.setArg(1, m_mapBuffers[B_buffer]);
            calcFluids.setArg(2, m_mapBuffers[B_flowRate]);
            calcFluids.setArg(3, m_mapBuffers[B_width]);
            calcFluids.setArg(4, m_mapBuffers[B_height]);
            calcFluids.setArg(5, m_mapBuffers[B_lenght]);

            cl_int errQ = m_optQueue->enqueueNDRangeKernel(calcFluids,cl::NullRange,cl::NDRange(bufLen/64)); // ceil n/64

            if (errQ != CL_SUCCESS)
                throw ;
            std::swap(m_mapBuffers[B_buffer], m_mapBuffers[i]);
        }
    PField pField(new Field(m_pState->size, m_pState->index + countSteps));
    for (int i = 0; i < LT__END; i++)
    {
        cl_int errEnQ = m_optQueue->enqueueReadBuffer(m_mapBuffers[i], CL_TRUE, 0, sizeof (int) * bufLen, &(pField->arrLiquids[i]));
        if (errEnQ != CL_SUCCESS)
            throw;
    }
    m_pState = pField;
    return pField;

}

bool MainEngine::buildProgram()
{
    std::string file_name = "/home/ivaz28/workspace/github/qblob_5.2/cyber_petry/gpu_core/engine/kernels/fluid.cl";
    std::ifstream sourceFile(file_name);
    if (!sourceFile.is_open())
    {
        std::cerr << file_name << " wasn't open\n";
        return false;
    }
    std::string sourceCode( std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));
    cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length()));

    cl::Program program(m_context, source);
    auto status = program.build({m_device}) ;
    if (status != CL_SUCCESS)
    {
        cl_int err;
        auto strError = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_device, &err);
        std::cerr << "Error building: " << strError << "\n";
        return false;
    }

    m_fluidProg = std::move(program);
    m_bfluidProg = true;
    return true;
}


