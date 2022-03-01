#pragma once

#include "../engine/types.h"
#include "colorengine.h"
#include "paintflags.h"
#include <vector>

namespace Draw
{

class CellColor
{
public:
    CellColor(eDrawObjects eDO = DO__All);
    QColor getQColor(Eng::CCell cell)const;
    QColor getColorLiquid(Eng::CCell cell, int index)const;
    eDrawObjects FDraw() const;

    void setFDraw(eDrawObjects newFDraw);

private:
    int m_spectrumLenght=32;
    eDrawObjects m_FDraw;   // flags
    std::vector<ColorEngine> m_fluids;
};
}
