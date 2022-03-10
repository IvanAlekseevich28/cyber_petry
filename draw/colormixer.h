#pragma once

#include "cellcolor.h"

namespace Draw
{
typedef unsigned char TClrChannel;
typedef std::pair<TClrChannel, QColor> PartClr;
typedef std::list<PartClr> LstPartClr;

class ColorMixer
{
public:
    ColorMixer();
    static QColor mix(const QColor& c1, const QColor& c2, TClrChannel p1);
    static QColor mix(const std::list<QColor> &lstClr);
    static QColor mix(const LstValClr &lstValClr);
    static void addClr(QColor& base, const QColor& extra, TClrChannel partOf256);
};
}
