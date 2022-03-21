#include "alg.h"

namespace Eng
{
inline void stayLiquid(CCell last, Cell& curr, TCount cn, TLiquid flowRate, eLiquidType eLT)
{
    TLiquid forNeighbours = cn * (last.arrLiquids[eLT] / flowRate);
    curr.arrLiquids[eLT] = last.arrLiquids[eLT] - forNeighbours;
}

inline void applyNeighbourLiquid(CCell nbr, Cell& curr, TLiquid flowRate, eLiquidType eLT)
{
    curr.arrLiquids[eLT] += nbr.arrLiquids[eLT] / flowRate;
}

void calcFluids(const ChunkRng rng, const Field& in, Field& out)
{
    const TCoord matW = in.m.size();
    const TCoord matH = in.getH();
    const TCoord maskX[] = {-1, 1, 0, 0};
    const TCoord maskY[] = { 0, 0,-1, 1};
    constexpr int maskLen = sizeof (maskX) / sizeof (TCoord);

    for (TCoord i = rng.first; i < rng.second; i++)
    {
        TCoord x = i % in.m.size();
        TCoord y = i / in.m.size();

        CCell inCell = in.m[x][y];
        Cell& outCell = out.m[x][y];

        TCount countNbrs = getCountNeighbours(x, y, matW, matH);
        for (TCount liq = 0; liq < LT__END; liq++)
            stayLiquid(inCell, outCell, countNbrs, in.flowsRate[liq], (eLiquidType)liq);
        for (int nbr = 0; nbr < maskLen; nbr++)
        {
            const TCoord nX = x + maskX[nbr];
            const TCoord nY = y + maskY[nbr];
            if (nY >= matH || nX >= matW || nX < 0 || nY < 0)
                continue;

            for (TCount liq = 0; liq < LT__END; liq++)
                applyNeighbourLiquid(in.m[nX][nY], outCell, in.flowsRate[liq], (eLiquidType)liq);

        }


    }
}
}
