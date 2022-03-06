#include "tools.h"
#include <cmath>

using namespace Eng;

// TODO
LstArea Tools::separateUp4Threads(const TCount nThread)
{
    LstArea lArea;

    const int countW = nThread;
    const int countH = (int)pow(nThread, 0.3334);

    const int chankLenY = MatH / countH;
    int residueY = MatH % countH;
    int iterY = 0;

    while (iterY < (int)MatH)
    {
        int allocatedY = chankLenY + (--residueY >= 0 ? 1 : 0);
        const int chankLenX = MatW / countW;
        int residueX = MatW % countW;
        int iterX = 0;

        while (iterX < (int)MatW)
        {
            int allocatedX = chankLenX + (--residueX >= 0 ? 1 : 0);

            lArea.push_back(Area(
                                Point(iterX, iterY),
                                Point(iterX+allocatedX, iterY+allocatedY))
                            );

            iterX += allocatedX;
        }
        iterY += allocatedY;
    }
    return lArea;
}

Tools::PointsRange::PointsRange(TCoord w, TCoord h) :
    m_area(Area(Point(0,0), Point(w,h))), m_iter(0,0) {}

Tools::PointsRange::PointsRange(CPoint lt, CPoint rb) : m_area(Area(lt, rb)), m_iter(lt) {}
Tools::PointsRange::PointsRange(CArea a) : m_area(a), m_iter(a.lt) {}
