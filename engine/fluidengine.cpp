#include "fluidengine.h"
#include "tools.h"

using namespace Eng;

FluidEngine::FluidEngine()
    : m_pField(new Field(0))
{
    // TODO
    m_lstFlows = Tools::separateUp4Threads(1);
}

PtrField FluidEngine::step(TCount steps)
{
    for (TCount i = 0; i < steps; i++)
        oneStep();
    return m_pField;
}

void FluidEngine::oneStep()
{
    PtrField pOutField(new Field(m_pField->index+1));

    MetaCells mc(m_pField, pOutField);
    for (CArea a : m_lstFlows)
    {
        calcOneChank(mc, a);
    }

    m_pField = pOutField;
}

void FluidEngine::calcOneChank(MetaCells& mc, CArea a)
{
    // TODO

    // calc liquids
    calcLiquids(mc, a);

    // calc liquids temp flows

    // calc flows

}

void FluidEngine::calcLiquids(MetaCells &mc, CArea a)
{
    Tools::PointsRange pr(a);
    while (!pr.isEnd())
    {
        auto lstNbs = getNeighbours(*pr);
        CCell inCell = mc.pin.m[pr.X()][pr.Y()];
        Cell& outCell = mc.pout.m[pr.X()][pr.Y()];

        outCell.stayLiquids(inCell, lstNbs.size());
        for (CDirPoint dpn : lstNbs)
        {
            CCell inNdCell = mc.pin.m[dpn.p.x][dpn.p.y];
            outCell.applyNeighbourLiquids(inNdCell, dpn.direct);
        }

        ++pr;
    }
}

// todo need for optimization by matrix Neighbours
LstDirPoints FluidEngine::getNeighbours(CPoint p)
{
    LstDirPoints lst;
    if (p.x != MatW-1)  lst.push_back(DirPoint(p.x+1, p.y, D_right));
    if (p.x != 0)       lst.push_back(DirPoint(p.x-1, p.y, D_left));
    if (p.y != MatH-1)  lst.push_back(DirPoint(p.x, p.y+1, D_top));
    if (p.y != 0)       lst.push_back(DirPoint(p.x, p.y-1, D_bottom));

    return lst;
}
