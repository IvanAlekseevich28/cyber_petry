#pragma once

#include "../core/entities/field.h"
#include "colormixer.h"

namespace Draw
{

typedef std::vector<std::vector<QColor> > ClrField;
typedef std::unique_ptr<ClrField> PClrField;

PClrField initClrField(const unsigned w, const unsigned h, const QColor& base = Qt::white);
PClrField convertField2Clr(const Eng::PCField in, const CellColor& cc, const Eng::TCount countThreads = 1);

}
