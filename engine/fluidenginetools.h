#pragma once

#include "fluidengine.h"

namespace Eng
{
class FluidEngineTools
{
public:
    FluidEngineTools();

    // tools
    void clear();
    void fillFieldByLiquid  (eLiquidType eLT, TLiquid val);
    bool addLiquid(CPoint p, eLiquidType eLT, TLiquid val);
    bool rmLiquid (CPoint p, eLiquidType eLT, TLiquid val);
};
}
