#pragma once

#include "../core/entities/cell.h"
#include "colorengine.h"
#include "gradientengine.h"
#include "paintflags.h"
#include <vector>

namespace Draw
{
typedef std::pair<Eng::TLiquid, QColor> ValClr;
typedef std::list<ValClr> LstValClr;

class CellColor
{
public:
    CellColor(eDrawObjects eDO = DO__All);
    QColor getQColor(Eng::CCell cell)const;
    ValClr getColorLiquid(Eng::CCell cell, int index)const;
    ValClr getColorWave(Eng::CCell cell)const;
    int FDraw() const;

    void setFDraw(int newFDraw);

private:
    int m_spectrumLenght=32;
    int m_FDraw;   // flags
    std::vector<ColorEngine> m_fluids;
    GradientEngine m_waves;
};
}
