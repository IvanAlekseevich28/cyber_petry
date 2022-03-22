#include "gradientengine.h"

using namespace Draw;

GradientEngine::GradientEngine(const QColor &minClr, const QColor &maxClr)
{
//    m_grad.setColorAt(0, minClr);
//    m_grad.setColorAt(1, maxClr);

    //    m_grad.
}

QColor GradientEngine::getColorByValue(const int value) const
{
    if (value == 0)
        return Qt::gray;
    if (value < 0)
        return Qt::white;

    for (int i = 0; i < 16; i++)
        if (value > (1 << (15 - i)))
        {
            int c = i << 2;
            return QColor(c,c,c);
        }

}
