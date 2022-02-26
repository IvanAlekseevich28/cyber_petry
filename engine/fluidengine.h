#pragma once

#include "types.h"
#include <list>

namespace Eng
{

class FluidEngine
{
public:
    FluidEngine(SimParams param);
    PtrField step(TCount steps);

    friend class FluidEngineTools;

private:
    void oneStep();
    inline void calcOnePoint(TCoord x, TCoord y, PtrField pOutField);

private:
    static void calcOneChank    (MetaCells &mc, CArea a);

    static void calcOneLiquid      (MetaCells &mc, CArea a, eLiquidType eLT = LT_water);
    static void calcAllLiquids     (MetaCells &mc, CArea a);
    static void calcLiquidsGrad (MetaCells &mc, CArea a);
    static void calcFlows       (MetaCells &mc, CArea a);

    static LstDirPoints getNeighbours(CPoint p);
    static LstDirPoints getNeighboursSolid(CPoint p, CField inF);

private:
    PtrField m_pField;
    LstArea m_lstFlows;
    SimParams m_params;
};
}
