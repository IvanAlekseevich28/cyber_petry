#pragma once

#include "IEngine.h"
#include "algs/alg.h"
#include <thread>

namespace Eng
{

class ChunkEngine : public IEngine
{
public:
    ChunkEngine(LstFunCalcs tasks);
    PProcess step(PProcess proc, const TCount countThreads) override;

private:
    LstFunCalcs m_pfCalcs;
    std::list<std::thread> m_threads;
};
}
