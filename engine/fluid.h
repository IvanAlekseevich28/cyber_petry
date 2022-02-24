#pragma once

#include "../common.h"

PtrGMat getMat(const Point &p, UShort val = 0);
UINT64 getSum(const PtrGMat pmat);
PtrGMat doFluid(const PtrGMat initPMat, const MSize &s);
void setMaxMinWather(PtrGMat pmat);
