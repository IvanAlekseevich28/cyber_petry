#include "fieldtools.h"
#include <cstdlib>
#include <ctime>

using namespace Eng;

FieldTools::FieldTools(PField pField) :
    m_pField(pField)
{
    srand(time(0));
}

void FieldTools::clear()
{
    const auto matLen = m_pField->getMatrixLen();
    const auto matH = m_pField->getH();
    for (TCount i = 0; i < matLen; i++)
    {
        TCoord x = i % matH;
        TCoord y = i / matH;

        Cell& curCell = m_pField->m[x][y];
        curCell.clear();
    }
}

void FieldTools::fillFieldByLiquid(eLiquidType eLT, TLiquid val)
{
    const auto matLen = m_pField->getMatrixLen();
    const auto matH = m_pField->getH();
    for (TCount i = 0; i < matLen; i++)
    {
        TCoord x = i % matH;
        TCoord y = i / matH;

        Cell& curCell = m_pField->m[x][y];
        curCell.arrLiquids[eLT] = val;
    }
}

void FieldTools::addRandomLiquid(TLiquid val)
{
    eLiquidType eLT = eLiquidType(rand() % LT__END);
    addRandomLiquid(val, eLT);
}

void FieldTools::addRandomLiquid(TLiquid val, eLiquidType eLT)
{
    const auto matH = m_pField->getH();

    Point rp(rand() % m_pField->m.size(), rand() % matH);
    addLiquid(rp, eLT, val);
}

bool FieldTools::addLiquid(CPoint p, eLiquidType eLT, TLiquid val)
{
    if (false == m_pField->inField(p))
        return false;

    Cell& curCell = m_pField->m[p.x][p.y];
    curCell.arrLiquids[eLT] += val;

    return true;
}

bool FieldTools::rmLiquid(CPoint p, eLiquidType eLT, TLiquid val)
{
    return addLiquid(p, eLT, -val);
}

bool FieldTools::addWaveNbrHeight(CPoint p, TWave val)
{
    addWaveHeight(p, val);
    auto lstNbr = m_pField->getNeighbours(p);
    for (const auto nbr : lstNbr)
        addWaveHeight(nbr, -(val / lstNbr.size()));

    return true;
}

bool FieldTools::addWaveHeight(CPoint p, TWave val)
{
    if (false == m_pField->inField(p))
        return false;

    Cell& curCell = m_pField->m[p.x][p.y];
    curCell.wave1 += val;
    curCell.wave2 = 0;

    return true;
}

void FieldTools::addRandomWaveHeight(TWave val)
{
    const auto matH = m_pField->getH();

    Point rp(rand() % m_pField->m.size(), rand() % matH);
    addWaveNbrHeight(rp, val);
}

void FieldTools::setPField(const PField &newPField)
{
    m_pField = newPField;
}
