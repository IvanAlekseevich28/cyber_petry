#pragma once

#include <list>

namespace Eng
{
typedef int TCoord;

struct Point
{
    TCoord x;
    TCoord y;

    explicit Point(TCoord x=0, TCoord y=0) : x(x), y(y) {}
    inline bool operator==(const Point& o)const
        {return (x == o.x) && (y == o.y);}
};
typedef const Point& CPoint;
typedef std::list<Point> Points;
}
