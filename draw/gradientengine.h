#pragma once

#include <QColor>
#include <QLinearGradient>

namespace Draw
{
class GradientEngine
{
public:
    GradientEngine(const QColor& minClr, const QColor& maxClr);
    QColor getColorByValue(const int value)const;

private:
    QLinearGradient m_grad;
};

}
