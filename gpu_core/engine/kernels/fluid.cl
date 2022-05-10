#define VALUES_PER_WORK_ITEM 64

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

void kernel calcFluids(global const int* arrIn, global int* arrOut, global const int* pFlowRate,
                       global const int* pW, global const int* pH, global const int* pLen)
{
    const int localId = get_local_id(0);
    const int groupId = get_group_id(0);
    const int groupSize = *pLen/VALUES_PER_WORK_ITEM;

    const int maskX[] = {-1, 1, 0, 0};
    const int maskY[] = { 0, 0,-1, 1};
    const int maskLen = sizeof (maskX) / sizeof (int);


    for (int i = 0; i < VALUES_PER_WORK_ITEM; ++i)
    {
        const int globPos = (groupId * groupSize * VALUES_PER_WORK_ITEM ) + (i * groupSize) + localId;
        if (globPos >= *pLen) return;

        const int x = globPos % *pW;
        const int y = globPos / *pW;

        const int* pInLiq  = &(arrIn [globPos]);
              int* pOutLiq = &(arrOut[globPos]);

        const int countNbrs = getCountNeighbours(x, y, *pW, *pH);
        stayLiquid(pInLiq, pOutLiq, countNbrs, *pFlowRate);

        for (int nbr = 0; nbr < maskLen; nbr++)
        {
            const int nX = x + maskX[nbr];
            const int nY = y + maskY[nbr];

            if (nY >= *pH || nX >= *pW || nX < 0 || nY < 0)
                continue;

            applyNeighbourLiquid(&arrIn[nX], pOutLiq, *pFlowRate);
        }
    }
}
