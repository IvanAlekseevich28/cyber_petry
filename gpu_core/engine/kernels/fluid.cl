#define VALUES_PER_WORK_ITEM 64

// CPU check
#if __cplusplus
    #include "../../entities/field.h"
    #define kernel '\ '
    #define global '\ '
#elif

#endif
inline int getCountNeighbours(const int x, const int y, const int matW, const int matH)
{
    if (x > 0 && y > 0 && x < matW-1 && y < matH-1) return 4;
    if ((x > 0 && y > 0) || (x < matW-1 && y < matH-1)) return 3;
    return 2;
}

inline void applyNeighbourLiquid(const int* pNbr, int* pCurr, const int flowRate)
{
    *pCurr += *pNbr / flowRate;
}

inline void stayLiquid(const int* pLast, int* pCurr, const int cn, const int flowRate)
{
    const int forNeighbours = cn * (*pLast / flowRate);
    *pCurr = *pLast - forNeighbours;
}

void kernel calcFluids(global const Field* pArrIn, global Field* pArrOut,
                       global const int* pW, global const int* pH, global const int* pLen,
                       global const Liquids* pFlowRate)
{

    const int countLiquids = sizeof(Liquids) / sizeof(int);
    const int localId = get_local_id(0);
    const int groupId = get_group_id(0);
    const int groupSize = pLen[0]/64;

    const int matW = N[0];
    const TCoord maskX[] = {-1, 1, 0, 0};
    const TCoord maskY[] = { 0, 0,-1, 1};
    const int maskLen = sizeof (maskX) / sizeof (int);


    for (int i = 0; i < VALUES_PER_WORK_ITEM; ++i)
    {
        const int atom = (groupId * groupSize * VALUES_PER_WORK_ITEM * countLiquids) + (i * groupSize * countLiquids) + localId;
        if (atom >= *pLen) return;

        const int linePos = atom / countLiquids;
        const int x = linePos % *pW;
        const int y = linePos / *pW;
        const int z = atom % countLiquids;

        const int* pInLiq  = &(  ( (int*)(pArrIn [linePos]) )[z]  );
              int* pOutLiq = &(  ( (int*)(pArrOut[linePos]) )[z]  );

        const int countNbrs = getCountNeighbours(x, y, *pW, *pH);
        stayLiquid(pInLiq, pOutLiq, countNbrs, pFlowRate[z]);

        for (int nbr = 0; nbr < maskLen; nbr++)
        {
            const int nX = x + maskX[nbr];
            const int nY = y + maskY[nbr];

            if (nY >= *pH || nX >= *pW || nX < 0 || nY < 0)
                continue;

            applyNeighbourLiquid(&inM[nX], outC, pFlowRate[z]);
        }
    }
}
