#pragma once

#include "types.h"

namespace Eng
{

inline TCount getCountNeighbours(const TCoord x, const TCoord y, const TCoord matW, const TCoord matH)
{
    if (x >= 0 && y >= 0 && x < matW && y < matH) return 4;
    if ((x >= 0 && y >= 0) || (x < matW && y < matH)) return 3;
    return 2;
}

void calcFluids(const ChunkRng rng, const Field& in, Field& out);
void calcWaves (const ChunkRng rng, const Field& in, Field& out);
}
