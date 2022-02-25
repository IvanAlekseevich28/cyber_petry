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

    for (CArea a : m_lstFlows)
    {
        calcOneChank(*m_pField, *pOutField, a);
    }

    m_pField = pOutField;
}

void FluidEngine::calcOneChank(const Field &in, Field &out, CArea a)
{
    Tools::PointsRange pr(a);
    while (!pr.isEnd())
    {
        // TODO

        // calc liquids
        // calc liquids temp flows
        // calc flows

        ++pr;
    }
}

