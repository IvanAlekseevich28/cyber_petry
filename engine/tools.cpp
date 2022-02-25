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

Tools::PointsRange &Tools::PointsRange::operator++()
{
//    if (!isEnd())
    m_iter.y += (m_iter.x+1) / m_area.rb.x;
    m_iter.x = (m_iter.x+1) % m_area.rb.x;
    return *this;
}

CPoint Tools::PointsRange::operator*() const
{
    return m_iter;
}

CPoint Tools::PointsRange::operator->() const
{
    return m_iter;
}

bool Tools::PointsRange::isEnd() const
{
    return m_iter == m_area.rb;
}
