#include "chunkengine.h"
#include "algs/threads.h"

using namespace Eng;

ChunkEngine::ChunkEngine(LstFunCalcs tasks) :
     m_pfCalcs(tasks) {}

PProcess ChunkEngine::step(PProcess proc, const TCount countThreads)
{
    ThreadInfo ti(0, countThreads);
    for (TCount i = 0; i < countThreads-1; i++)
    {
        ti.indexThread = i;
        m_threads.push_back(
                    std::thread(
                        threadCalc,
                        std::cref(m_pfCalcs),
                        ti,
                        std::cref(*(proc->last)),
                        std::ref(*(proc->curr)))
                    );
    }

    ti.indexThread = countThreads-1;
    threadCalc(m_pfCalcs, ti,*(proc->last), *(proc->curr));

    for (auto& thr : m_threads)
        thr.join();

    m_threads.clear();
    return proc;
}
