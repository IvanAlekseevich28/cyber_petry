#pragma once

#include "types.h"
#include <list>

namespace Eng
{

class FluidEngine
{
public:
    FluidEngine();
    PtrField step(TCount steps);

    friend class FluidEngineTools;

private:
    void oneStep();
    inline void calcOnePoint(TCoord x, TCoord y, PtrField pOutField);

private:
    static void calcOneChank    (MetaCells &mc, CArea a);

    static void calcLiquids     (MetaCells &mc, CArea a);
    static void calcLiquidsGrad (MetaCells &mc, CArea a);
    static void calcFlows       (MetaCells &mc, CArea a);

    static LstPoints getNeighbours(CPoint p);

private:
    PtrField m_pField;
    LstArea m_lstFlows;
};
}
