#pragma once

#include <QColor>
#include "../engine/types.h"
#include "paintflags.h"

namespace Draw
{
typedef unsigned char TClrChannel;

class ColorMixer
{
public:
    ColorMixer();
    static QColor mix(const QColor& c1, const QColor& c2, TClrChannel p1);
    static QColor mix(const std::list<QColor> &lstClr);
    static void addClr(QColor& base, const QColor& extra, TClrChannel partOf256);
};
}
