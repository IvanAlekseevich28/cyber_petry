#include "fluidenginetools.h"
#include "tools.h"
#include <cstdlib>

using namespace Eng;

FluidEngineTools::FluidEngineTools(FluidEngine &eng) :
    m_eng(eng)
{
    srand(time(0));
}

void FluidEngineTools::clear()
{
    Tools::PointsRange pr(Point(0,0), Point(MatW, MatH));
    while (pr.isEnd() == false)
    {
        Cell& curCell = m_eng.m_pField->m[pr.X()][pr.Y()];
        curCell.clear();
        ++pr;
    }
}

void FluidEngineTools::fillFieldByLiquid(eLiquidType eLT, TLiquid val)
{
    Tools::PointsRange pr(Point(0,0), Point(MatW, MatH));
    while (pr.isEnd() == false)
    {
        Cell& curCell = m_eng.m_pField->m[pr.X()][pr.Y()];
        curCell.arrLiquids[eLT] = val;
        ++pr;
    }
}

void FluidEngineTools::addRandomLiquid(TLiquid val)
{
    Point rp(rand() % MatW, rand() % MatH);
    eLiquidType eLT = eLiquidType(rand() % LT__END);
    addLiquid(rp, eLT, val);
}

bool FluidEngineTools::addLiquid(CPoint p, eLiquidType eLT, TLiquid val)
{
    if (!p.inField())
        return false;

    Cell& curCell = m_eng.m_pField->m[p.x][p.y];
    curCell.arrLiquids[eLT] += val;

    return true;
}

bool FluidEngineTools::rmLiquid(CPoint p, eLiquidType eLT, TLiquid val)
{
    return addLiquid(p, eLT, -val);
}

