#include "tools.h"

using namespace Eng;

// TODO
LstArea Tools::separateUp4Threads(const TCount nThread)
{
    LstArea lArea = {Area(Point(0,0), Point(MatW, MatW))};

    return lArea;
}

Tools::PointsRange::PointsRange(CPoint lt, CPoint rb) : m_area(Area(lt, rb)), m_iter(lt) {}
Tools::PointsRange::PointsRange(CArea a) : m_area(a), m_iter(a.lt) {}
