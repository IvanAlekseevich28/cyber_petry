#pragma once

#include "types.h"

namespace Eng {
namespace Tools
{
// TODO. It returns one chank.
LstArea separateUp4Threads(const TCount nThread);

class PointsRange
{
public:
    PointsRange(TCoord w, TCoord h);
    PointsRange(CPoint lt, CPoint rb);
    PointsRange(CArea a);

    inline PointsRange& operator++()  // prefix
    {
        m_iter.y += (m_iter.x+1) / m_area.rb.x;
        m_iter.x = (m_iter.x+1) % m_area.rb.x;
        return *this;
    }

    inline CPoint operator*()const {return m_iter;}
    inline TCoord X()const {return m_iter.x;}
    inline TCoord Y()const {return m_iter.y;}
    inline bool isEnd()const {return m_iter.y == m_area.rb.y;}
private:
    Area m_area;
    Point m_iter;
};

}}
