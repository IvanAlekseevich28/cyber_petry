#include "colormixer.h"
#include <algorithm>

#define CHNLEN 256 // color channel lenght

using namespace Draw;

ColorMixer::ColorMixer()
{

}

QColor ColorMixer::mix(const QColor &c1, const QColor &c2, TClrChannel p1)
{
    QColor c3;
    c3.setRed   ((c1.red()      * (CHNLEN - p1) / CHNLEN) + (c2.red()   * p1 / CHNLEN));
    c3.setGreen ((c1.green()    * (CHNLEN - p1) / CHNLEN) + (c2.green() * p1 / CHNLEN));
    c3.setBlue  ((c1.blue()     * (CHNLEN - p1) / CHNLEN) + (c2.blue()  * p1 / CHNLEN));
    return c3;
}

QColor ColorMixer::mix(const std::list<QColor> &lstClr)
{
    if (lstClr.empty())
        return QColor(255,255,255);

    auto iter = lstClr.begin();
    QColor base = *(iter++);
    TClrChannel partOf256 = CHNLEN / lstClr.size();
    for (; iter != lstClr.end(); iter++)
        addClr(base, *iter, partOf256);
    return base;
}

QColor ColorMixer::mix(const LstValClr &lstValClr)
{
    if (lstValClr.empty())
        return QColor(255,255,255);

    long long valsSum =  0;
    for (const auto& valClr : lstValClr)
        valsSum += valClr.first;

    LstPartClr lstPartClr;
    for (const auto& valClr : lstValClr)
    {
        TClrChannel partOf256 = (long long)valClr.first * CHNLEN / valsSum;
        lstPartClr.push_back(std::make_pair(partOf256, valClr.second));
    }

    int r(0), g(0), b(0);
    for (const auto& partClr : lstPartClr)
    {
        r += partClr.second.red()   * partClr.first / CHNLEN;
        g += partClr.second.green() * partClr.first / CHNLEN;
        b += partClr.second.blue()  * partClr.first / CHNLEN;
    }
    return QColor(r,g,b);
}

void ColorMixer::addClr(QColor &base, const QColor &extra, TClrChannel partOf256)
{
    base.setRed   ((base.red()      * (CHNLEN - partOf256) / CHNLEN) + (extra.red()   * partOf256 / CHNLEN));
    base.setGreen ((base.green()    * (CHNLEN - partOf256) / CHNLEN) + (extra.green() * partOf256 / CHNLEN));
    base.setBlue  ((base.blue()     * (CHNLEN - partOf256) / CHNLEN) + (extra.blue()  * partOf256 / CHNLEN));
}
