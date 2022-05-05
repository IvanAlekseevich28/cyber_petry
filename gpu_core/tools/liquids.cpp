#include "liquids.h"

Liquids initLiquids(const int defValue)
{
    Liquids liquids;
    for (size_t i = 0; i < sizeof (Liquids) / sizeof (int); i++)
        reinterpret_cast<int*>(&liquids)[i] = defValue;

    return liquids;
}
