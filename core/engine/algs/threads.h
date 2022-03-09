#pragma once

#include "types.h"

namespace Eng
{
ChunkRng getRngOfThread(const ThreadInfo ti, const TCount len);

void threadCalc(const LstFunCalcs& tasks, const ThreadInfo ti, const Field& in, Field& out);
}
