#include "mainengine.h"
#include "algs/alg.h"
#include "chunkengine.h"

namespace Eng
{
MainEngine::MainEngine(PField state) :
    m_pState(state)
{
    LstFunCalcs tasks {calcFluids, calcWaves/*, rendWaves*/};
    m_engines.push_back(PIEngine(new ChunkEngine(tasks)));
}

const PField Eng::MainEngine::step(const TCount countThreads)
{
    std::lock_guard<std::mutex> lk(m_MCalulating);
    PProcess proc = startProc(m_pState);

    for (auto& eng : m_engines)
        proc = eng->step(move(proc), countThreads);

    m_pState.reset();
    m_pState = endProc(move(proc));
    return m_pState;
}

PField MainEngine::getState()
{
    std::lock_guard<std::mutex> lk(m_MCalulating);
    return m_pState;
}

PCField MainEngine::getConstState()const
{
    std::lock_guard<std::mutex> lk(m_MCalulating);
    return m_pState;
}

void MainEngine::setState(const PField &newPState)
{
    std::lock_guard<std::mutex> lk(m_MCalulating);
    m_pState = newPState;
}
}
