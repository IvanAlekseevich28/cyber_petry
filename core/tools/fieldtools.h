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
    void addRandomLiquid(TLiquid val, eLiquidType eLT);
    bool addLiquid(CPoint p, eLiquidType eLT, TLiquid val);
    bool rmLiquid (CPoint p, eLiquidType eLT, TLiquid val);

    bool addWaveNbrHeight(CPoint p, TWave val);
    bool addWaveHeight(CPoint p, TWave val);
    void addRandomWaveHeight(TWave val);

    void setPField(const PField &newPField);

private:
    PField m_pField;
};
}
