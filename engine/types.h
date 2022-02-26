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
typedef unsigned TLight;
typedef unsigned TFlags;

struct SimParams
{
    bool hasAllLiquids  =false;
    bool hasSolid       =false;
    bool hasLights      =false;
    bool hasHeat        =false;
    bool hasFlow        =false;

    SimParams(bool hasAllLiquids = false,
              bool hasSolid = false, bool hasLights = false,
              bool hasHeat = false, bool hasFlow = false);
};
typedef const SimParams& CSimParams;

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
    TLight irgb; // infra-red|red|green|blue
    TFlags sld; // it has 4 elems of 8 bit len
    Flow flow;

    Cell();

    void stayLiquids(const Cell &last, TCount cn);
    inline void stayLiquid(const Cell& last, TCount cn, eLiquidType eLT)
    {
        TCount forNeighbours = cn * (last.arrLiquids[eLT] / 5);
        arrLiquids[eLT] = last.arrLiquids[eLT] - forNeighbours;
    }

    void applyNeighbourLiquids(const Cell& nbr);
    inline void applyNeighbourLiquid(const Cell& nbr, eLiquidType eLT)
    {arrLiquids[eLT] += nbr.arrLiquids[eLT] / 5;}

    TLiquid getLiquidsSum()const;
    inline bool isSolid()const {return sld & 0x00FFFFFF;};

    inline TFlow calcGrad(const Cell& last)const
    {return getLiquidsSum() - last.getLiquidsSum();}

    TCount getFlowBonus(const Cell& n, eDirection dir, TCount onePart=50);
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
typedef const Field& CField;

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
    CField pin;
    Field& pout;
    CSimParams params;
    LiquidsGrad lg;


    MetaCells (const PtrField& in, PtrField& out, CSimParams p) :
        pin(*in), pout(*out), params(p) {}
};

}
