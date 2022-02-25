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
    PointsRange(CPoint lt, CPoint rb);
    PointsRange(CArea a);

    inline PointsRange& operator++();  // prefix
    inline CPoint operator*()const;
    inline CPoint operator->()const;
    inline TCoord X()const {return m_iter.x;}
    inline TCoord Y()const {return m_iter.y;}
    inline bool isEnd()const;
private:
    Area m_area;
    Point m_iter;
};

}}
