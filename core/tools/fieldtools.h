#pragma once

#include "../entities/field.h"

namespace Eng
{
class FieldTools
{
public:
    FieldTools(PField pField);

    // tools
    void clear();
    void fillFieldByLiquid  (eLiquidType eLT, TLiquid val);
    void addRandomLiquid(TLiquid val);
    bool addLiquid(CPoint p, eLiquidType eLT, TLiquid val);
    bool rmLiquid (CPoint p, eLiquidType eLT, TLiquid val);

    void setPField(const PField &newPField);

private:
    PField m_pField;
};
}
