#include "alg.h"

namespace Eng
{
inline void stayLiquid(CCell last, Cell& curr, TCount cn, TLiquid flowRate, eLiquidType eLT)
{
    TLiquid forNeighbours = cn * (last.arrLiquids[eLT] / 5 / flowRate);
    curr.arrLiquids[eLT] = last.arrLiquids[eLT] - forNeighbours;
}

inline void applyNeighbourLiquid(CCell nbr, Cell& curr, TLiquid flowRate, eLiquidType eLT)
{
    curr.arrLiquids[eLT] += nbr.arrLiquids[eLT] / 5 / flowRate;
}

void calcFluids(const ChunkRng rng, const Field& in, Field& out)
{
    for (int i = rng.first; i < rng.second; i++)
    {
        int x = i % in.m.size();
        int y = i / in.m.size();

        auto lstNbs = in.getNeighbours(Point(x,y));
        CCell inCell = in.m[x][y];
        Cell& outCell = out.m[x][y];

        for (TCount i = 0; i < LT__END; i++)
        {
            stayLiquid(inCell, outCell, lstNbs.size(), in.flowsRate[i], (eLiquidType)i);
            for (CPoint n : lstNbs)
                applyNeighbourLiquid(in.m[n.x][n.y], outCell, in.flowsRate[i], (eLiquidType)i);
        }
    }
}
}
