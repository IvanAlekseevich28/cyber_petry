#include "inputengine.h"

using namespace Eng;

InputEngine::InputEngine(PField pFld) : m_tool(pFld)
{
    reset();
}

bool Eng::InputEngine::input(PField pFld)
{
    if (pFld.get() == nullptr)
        return false;

    const int index = pFld->index;
    if (index <= m_processedIndex)
        return true;

    m_tool.setPField(pFld);

    const auto matW = pFld->m.size();
    const auto matH = pFld->getH();

    if (index < 50)
    {
        Point ip(index*5, index*3);
        if(pFld->inField(ip))
        {
            m_tool.addLiquid(ip, LT_water, 0x10000);
        }
    }

    m_processedIndex = index;
    return true;
}

void InputEngine::reset()
{
    m_processedIndex=-1;
}
