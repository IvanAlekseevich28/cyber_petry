#pragma once

#include <vector>
#include <map>
#include <memory>
#include <QColor>
#include <string>
#include "minmax.h"
#include "types.h"

namespace Draw
{
struct ClrEngParams
{
    MinMax S = MinMax(16,255);
    MinMax V = MinMax(255,255);
    TIntNum specLen = 16;
    TIntNum maxValue = 0x8FFFFFFF;
    ClrEngParams(){}
    ClrEngParams(int maxS, int minV, int pow2, int spLen) :
        S(MinMax(16,maxS)), V(MinMax(minV,255)),
        specLen(spLen), maxValue(1 << pow2) {}
};

class ColorEngine
{
public:
    enum eScaleType
    {
        ST_log,
        ST_pow2,

        ST__End
    };
    ColorEngine(TRGB rgb, ClrEngParams params = ClrEngParams());

    QColor getColorByValue(const TIntNum &value, eScaleType eST = ST_log, const QColor &base = Qt::white)const;
    std::vector<QColor> genSpec()const;

    void setBaseColor(TRGB rgb);
    void setBaseColor(QColor clr);

    QColor getBaseColor()const;

    void setSpecLen(const TIntNum &newSpecLen);

    void setMaxValue(const TIntNum &newMaxValue);

    void setS(MinMax newS);

    void setV(MinMax newV);

    void setParams(const ClrEngParams &newParams, bool noCalc = false);

    const TScale scale(eScaleType eST = ST_log) const;

    const ClrEngParams &params() const;

    static std::string int2Str(TIntNum num);

private:
    void recalcScale();
    TScale genLogScale()const;
    TScale genPow2Scale()const;
    static QColor int2Clr(TRGB rgb);
    static int correctSLvalues(int val);

private:
    int m_baseH;
    int m_baseS;
    int m_baseV;

    ClrEngParams m_params;
    std::vector<QColor> m_colorSpectrum;
    TScale m_logScale;
    TScale m_pow2Scale;
};
typedef std::unique_ptr<ColorEngine> PtrColorEngine;
}
