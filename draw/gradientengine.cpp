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
    {
        for (int i = 0; i < 16; i++)
            if (-value > (1 << (15 - i)))
            {
                int c = 128 + (i << 3);
                return QColor(c,c,c);
            }
    }

    for (int i = 0; i < 16; i++)
        if (value > (1 << (15 - i)))
        {
            int c = i << 3;
            return QColor(c,c,c);
        }
    return Qt::gray;
}
