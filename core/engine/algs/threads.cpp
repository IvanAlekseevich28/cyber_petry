#include "threads.h"

namespace Eng
{

ChunkRng getRngOfThread(const ThreadInfo ti, const TCount len)
{
    const int chunkLen = len / ti.countThreads;
    const int chunksPlusOneCount = len % ti.countThreads;

    const int startRng = (chunkLen*ti.indexThread) +
            (ti.indexThread < chunksPlusOneCount ? ti.indexThread : chunksPlusOneCount);
    const int endRng = startRng + chunkLen + int(chunksPlusOneCount > ti.indexThread);

    return std::make_pair(startRng, endRng);
}

void threadCalc(const LstFunCalcs& tasks, const ThreadInfo ti, const Field& in, Field& out)
{
    const auto rng = getRngOfThread(ti, in.getMatrixLen());
    for (const auto task : tasks)
        task(rng, in, out);
}
}
