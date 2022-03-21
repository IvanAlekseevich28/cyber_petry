#include "alg.h"

namespace Eng
{
void calcWaves(const ChunkRng rng, const Field& in, Field& out)
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

        Cell& outCell = out.m[x][y];

        TWave sumLastNbrWaves(0);
        TCount countNbrs(0);

        for (int nbr = 0; nbr < maskLen; nbr++)
        {
            const TCoord nX = x + maskX[nbr];
            const TCoord nY = y + maskY[nbr];
            if (nY >= matH || nX >= matW || nX < 0 || nY < 0)
                continue;

            CCell inNbrCell = in.m[nX][nY];

            sumLastNbrWaves += inNbrCell.wave1;
            countNbrs++;
        }

        CCell inCell = in.m[y][x];
        outCell.wave2 = outCell.wave1;

        outCell.wave1 =  (sumLastNbrWaves / 2) - inCell.wave2;
        outCell.wave1 -= (outCell.wave1 >> in.wavePowerLosingPow2); // losing wave power
        int zz =1;
    }
}
}
