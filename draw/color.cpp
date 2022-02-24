#include "color.h"

static const UINT blueGrad[] = {0x7878FF, 0x5C5CFF, 0x4242FF, 0x2A2AFF, 0x1414FF, 0x0000FF, 0x0000EB, 0x0000D8, 0x0000C7, 0x0000B7, 0x0000A8};
static const UINT blueGradSize = sizeof (blueGrad) / sizeof (UINT);
// No check
int getArrIndex(UShort val, const MaxMin& mmw, int arrSize)
{
    const int range = mmw.max - mmw.min;
    const int mval = val - mmw.min;
    if (mval < arrSize)
        return mval;

    const int step = range / arrSize;
    return mval / step;
}

QColor int2Clr(UINT rgb)
{
    QColor qclr;
    qclr.setRed((rgb & 0xff0000) >> 16);
    qclr.setGreen((rgb & 0x00ff00) >> 8);
    qclr.setBlue(rgb & 0x0000ff);
    return qclr;
}

QColor getWatherCellColor(UShort wather, const MaxMin& mmw)
{
    UINT nRGB = blueGrad[getArrIndex(wather, mmw, blueGradSize)];
    return int2Clr(nRGB);
}
