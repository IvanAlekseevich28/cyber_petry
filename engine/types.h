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
    LT_water,
    LT_oxygen,
    LT_carbon,
    LT_nitrogen,
    LT_acid,
    LT_organic,

    LT__END
};

enum eDirection : char
{
    D_none      = 0,
    D_top       = 1,
    D_left      = 2,
    D_bottom    = 4,
    D_right     = 8,

};

typedef int TLiquid;
typedef int TFlow;
typedef int TCoord;
typedef unsigned TCount;

struct Flow
{
    TFlow xSpd;
    TFlow ySpd;
    Flow(TFlow x=0, TFlow y=0) :
        xSpd(x), ySpd(y) {}
    Flow &operator+=(const Flow& oth);
    Flow split(TFlow numerator, TFlow denominator=32, bool sqrt2=false, bool isLandT = true);
};

struct Cell
{
    std::array<TLiquid, LT__END> arrLiquids;
    Flow flow;

    Cell();

    inline TLiquid getLiquidsSum()const;
    inline void applyNeighbourLiquids(const Cell& n, eDirection dir);
    inline TFlow calcGrad(const Cell& last)const;
    inline void stayLiquids(const Cell& last, TCount cn);
    inline TCount getFlowBonus(const Cell& n, eDirection dir, TCount onePart=50);
//    inline TFlow
};
typedef const Cell& CCell;
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
    inline eDirection getRelativelyDirection(const Point& o)const;
};
typedef const Point& CPoint;
typedef std::list<Point> LstPoints;

struct DirPoint
{
    Point p;
    eDirection direct;
    DirPoint(CPoint point, eDirection direction=D_none);
    DirPoint(TCoord x, TCoord y, eDirection direction=D_none);
};
typedef const DirPoint& CDirPoint;
typedef std::list<DirPoint> LstDirPoints;

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
    const Field &pin;
    Field& pout;
    LiquidsGrad lg;

    MetaCells (const PtrField& in, PtrField& out) :
        pin(*in), pout(*out) {}
};

}
