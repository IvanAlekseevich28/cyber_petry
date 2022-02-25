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
    static void calcOneChank    (const Field& in, Field& out, CArea a);

    static void calcLiquids     (const Field& in, Field& out, CArea a);
    static void calcLiquidsFlows(const Field& in, Field& out, CArea a);
    static void calcFlows       (const Field& in, Field& out, CArea a);

private:
    PtrField m_pField;
    LstArea m_lstFlows;
};
}
