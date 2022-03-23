#pragma once

#include <QColor>
#include <map>
#include <vector>
#include "types.h"

namespace Draw
{
class GradientEngine
{
public:
    GradientEngine(int specLen, int val, const QColor& minClr, const QColor& maxClr);
    GradientEngine(int specLen, int val, const QColor& minClr, const QColor& zeroClr, const QColor& maxClr);

    QColor getColorByValue(const int value)const;

    static Scale genScale(int specLen, const QColor& minClr, const QColor& maxClr);

private:
    void genLogScale(int maxValue, const Scale& scale);

private:
    bool m_isThreeClr;
    TScale m_logScale;
};

}
