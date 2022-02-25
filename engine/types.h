#pragma once

#include <array>
#include <memory>
#include <list>


namespace Eng
{
constexpr unsigned MatW = 100;
constexpr unsigned MatH = 100;

enum eLiquidType
{
    LT_oxygen,
    LT_carbon,
    LT_nitrogen,
    LT_organic,

    LT__END
};
typedef int TLiquid;
typedef int TFlow;
typedef unsigned TCoord;
typedef unsigned TCount;

struct Flow
{
    TFlow xSpd;
    TFlow ySpd;
    Flow(TFlow x=0, TFlow y=0) :
        xSpd(x), ySpd(y) {}
    Flow &operator+=(const Flow& oth);
    Flow split(TFlow numerator, TFlow denominator=32, bool sqrt2=false);
};

struct Cell
{
    std::array<TLiquid, LT__END> arrLiquids;
    Flow flow;
};
typedef std::array<std::array<Cell, MatH>, MatW> CellMatrix;

struct Field
{
    Field(TCount index = 0) :
        index(index) {}

    CellMatrix m;
    unsigned index;
};
typedef std::shared_ptr<Field> PtrField;

struct MSize
{
    TCoord h;
    TCoord w;
    MSize(TCoord H, TCoord W) :
        h(H), w(W) {}
};

struct Point
{
    TCoord x;
    TCoord y;
    Point(TCoord x=0, TCoord y=0) : x(x), y(y) {}
    bool operator==(const Point& o)const
        {return (x == o.x) && (y == o.y);}
};
typedef const Point& CPoint;

struct Area
{
    Point lt;
    Point rb;
    Area(CPoint lt, CPoint rb):
        lt(lt), rb(rb) {}
};
typedef const Area& CArea;
typedef std::list<Area> LstArea;

typedef std::array<std::array<TFlow, MatH>, MatW> LiquidsGrad;

struct MetaCells
{
    const PtrField pin;
    PtrField pout;
    LiquidsGrad lg;

    MetaCells (const PtrField in, PtrField out) :
        pin(in), pout(out) {}
};

}
