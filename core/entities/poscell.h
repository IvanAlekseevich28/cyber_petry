#pragma once

#include "cell.h"
#include "point.h"

namespace Eng
{
struct PosCell : public Point, public Cell
{
    PosCell(CPoint p, CCell c) :
        Point(p), Cell(c) {}

    PosCell(CPoint p, eLiquidType eLT, TLiquid val) :
        Point(p)
    {
        Cell::arrLiquids[eLT] = val;
    }

    PosCell(CPoint p, const TLiquids& mix) :
        Point(p)
    {
        Cell::arrLiquids = mix;
    }

    PosCell(CPoint p, TWave wave1, TWave wave2=0) :
        Point(p)
    {
        Cell::wave1 = wave1;
        Cell::wave2 = wave2;
    }
};
}
