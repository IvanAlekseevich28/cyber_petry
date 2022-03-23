#include "gradientengine.h"
#include <cmath>

using namespace Draw;

GradientEngine::GradientEngine(int specLen, int val, const QColor &minClr, const QColor &maxClr)
{
    auto scale = genScale(specLen, minClr, maxClr);
    genLogScale(val, scale);
}

GradientEngine::GradientEngine(int specLen, int val, const QColor &minClr, const QColor &zeroClr, const QColor &maxClr)
{
    auto positiveScale = genScale(specLen, zeroClr, maxClr);
    auto negativeScale = genScale(specLen, minClr, zeroClr);
    genLogScale(val, positiveScale);

    TScale tempNegativeLogScale;
    int i = 0;
    for (const auto& valClr : m_logScale)
        tempNegativeLogScale.insert(std::make_pair(-valClr.first, negativeScale[i++]));
    m_logScale.insert(tempNegativeLogScale.begin(), tempNegativeLogScale.end());
}

QColor GradientEngine::getColorByValue(const int value) const
{
    if (value >= m_logScale.rbegin()->first)
        return m_logScale.rbegin()->second;
    else if (value <= m_logScale.begin()->first)
        return m_logScale.begin()->second;

    return m_logScale.lower_bound(value)->second;
}

void GradientEngine::genLogScale(int maxValue, const Scale &scale)
{
    const TFltNum power = std::log(maxValue) / std::log(scale.size());
    for (unsigned x = 0; x < scale.size(); x++)
    {
        TIntNum limit = pow(x, power);
        m_logScale.insert(std::make_pair(limit, scale[x]));
    }
}

Scale GradientEngine::genScale(int specLen, const QColor &minClr, const QColor &maxClr)
{
    if (specLen < 2)
        return {};

    Scale scale;

    double stepR = static_cast<double>(maxClr.red()     - minClr.red())     / (specLen-1);
    double stepG = static_cast<double>(maxClr.green()   - minClr.green())   / (specLen-1);
    double stepB = static_cast<double>(maxClr.blue()    - minClr.blue())    / (specLen-1);

    for (int i = 0; i < specLen; i++)
    {
        QColor clr;
        clr.setRed  (static_cast<unsigned char>(minClr.red()     +  stepR * i));
        clr.setGreen(static_cast<unsigned char>(minClr.green()   +  stepG * i));
        clr.setBlue (static_cast<unsigned char>(minClr.blue()    +  stepB * i));
        scale.push_back(clr);
    }

    return scale;
}
