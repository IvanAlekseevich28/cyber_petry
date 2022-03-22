#include "cellcolor.h"
#include "colormixer.h"

using namespace Draw;

CellColor::CellColor(eDrawObjects eDO) : m_spectrumLenght(64), m_FDraw(eDO), m_fluids
{
    ColorEngine(0x0000ff, Draw::ClrEngParams(255, 185, 31, m_spectrumLenght)),
    ColorEngine(0x0040ff, Draw::ClrEngParams(127, 255, 29, m_spectrumLenght)),
    ColorEngine(0x000000, Draw::ClrEngParams(255,  30, 26, m_spectrumLenght)),
    ColorEngine(0xffff00, Draw::ClrEngParams(255, 166, 31, m_spectrumLenght)),
    ColorEngine(0xff00ff, Draw::ClrEngParams(255,  98, 27, m_spectrumLenght)),
    ColorEngine(0x00ff00, Draw::ClrEngParams(255,  64, 28, m_spectrumLenght))
},
m_waves
(
    GradientEngine(Qt::white, Qt::black)
)
{

}

QColor CellColor::getQColor(Eng::CCell cell) const
{
    LstValClr clrMix;
    for (int i = 0; i < Eng::LT__END; i++)
        if (m_FDraw & (1 << i) && cell.arrLiquids[i] > 0)
            clrMix.push_back(getColorLiquid(cell, i));

    if (m_FDraw & DO_waves && cell.wave > 0)
        clrMix.push_back(getColorWave(cell));

    return ColorMixer::mix(clrMix);
}

ValClr CellColor::getColorLiquid(Eng::CCell cell, int index) const
{
    const auto liquidVal = cell.arrLiquids[index];
    const auto clr = m_fluids[index].getColorByValue(liquidVal);
    return std::make_pair(liquidVal, clr);
}

ValClr CellColor::getColorWave(Eng::CCell cell) const
{
    auto waveVal = cell.wave;
    const auto clr = m_waves.getColorByValue(waveVal);
    waveVal = waveVal > 0 ? waveVal : -waveVal;

    return std::make_pair(waveVal, clr);
}

int CellColor::FDraw() const
{
    return m_FDraw;
}

void CellColor::setFDraw(int newFDraw)
{
    m_FDraw = newFDraw;
}
