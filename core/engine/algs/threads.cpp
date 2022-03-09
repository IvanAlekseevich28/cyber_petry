#include "threads.h"

namespace Eng
{

ChunkRng getRngOfThread(const ThreadInfo ti, const TCount len)
{
    const int chankLen = len / ti.countThreads;
    const int chanksPlusOneCount = len % ti.countThreads;

    const int startRng = (chankLen*ti.indexThread) +
            (chanksPlusOneCount % (ti.indexThread+1));
    const int endRng = startRng + chankLen + int(chanksPlusOneCount > ti.indexThread);

    return std::make_pair(startRng, endRng);
}

void threadCalc(const LstFunCalcs& tasks, const ThreadInfo ti, const Field& in, Field& out)
{
    const auto rng = getRngOfThread(ti, in.getMatrixLen());
    for (const auto task : tasks)
        task(rng, in, out);
}
}
