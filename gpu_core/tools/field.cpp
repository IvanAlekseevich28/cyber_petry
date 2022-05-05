#include "field.h"
#include <string.h>

PField initField(const TSize size, OptLiquids initLiquids, OptLiquids flowRate)
{
    PField pField(new Field);
    const int lenght = size.w * size.h;

    // Liquids
    pField->arrLiquids = new Liquids[lenght];

    if (initLiquids.has_value() == false)
    {
        Liquids init;
        memset(&init, 0, sizeof (Liquids));
        initLiquids = init;
    }
    for (int i = 0; i < lenght; i++)
        pField->arrLiquids[i] = *initLiquids;

    if (flowRate.has_value() == false)
    {
        Liquids defFlowRate;
        for (size_t i = 0; i < sizeof (Liquids) / sizeof (int); i++)
            reinterpret_cast<int*>(&defFlowRate)[i] = 5;
        defFlowRate.acid        *= 4;
        defFlowRate.nitrogen    *= 2;
        defFlowRate.carbon      *= 32;
        defFlowRate.organic     *= 16;

        flowRate = defFlowRate;
    }
    pField->flowRate = *flowRate;

    return pField;
}

void deleteField(PField pField)
{
    if (!pField)
        return;

    if (pField->arrLiquids != nullptr)
    {
        delete [] pField->arrLiquids;
        pField->arrLiquids = nullptr;
    }
}
