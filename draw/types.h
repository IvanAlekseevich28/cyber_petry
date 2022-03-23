#pragma once

#include <map>
#include <vector>
#include <QColor>

namespace Draw
{
typedef unsigned TRGB;
typedef int TIntNum;
typedef double TFltNum;
typedef std::map<TIntNum, QColor> TScale;
typedef std::vector<QColor> Scale;
}
