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

    PointsRange& operator++();  // prefix
    bool isEnd()const;
private:
    Area m_area;
    Point m_iter;
};

}}
