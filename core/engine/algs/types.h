#pragma once

#include <list>
#include "../../entities/process.h"

namespace Eng
{

struct ThreadInfo
{
    int indexThread;
    int countThreads;
    ThreadInfo(int idx, int count) :
        indexThread(idx), countThreads(count) {}
};

typedef std::pair<int, int> ChunkRng;
using pFunCalc = void (*)(const ChunkRng rng, const Field& in, Field& out);
typedef std::list<pFunCalc> LstFunCalcs;
}
