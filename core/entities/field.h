#pragma once

#include "cell.h"
#include "point.h"
#include "../../structs/size.h"
#include <vector>
#include <memory>

#include <QMetaType>

namespace Eng
{
typedef std::vector<std::vector<Cell> > CellMatrix;

struct Field
{
    CellMatrix m;
    TLiquids flowsRate;
    TCount wavePowerLosingPow2;

    const unsigned index;

    explicit Field(const TCoord w, const TCoord h);
    explicit Field(const Field& oth);

    bool inField(CPoint p)const;
    Points getNeighbours(CPoint p)const;
    TCount getMatrixLen()const;
    inline TCount getH()const
        {return m[0].size();}
    inline TSize getSize()const
        {return TSize(m.size(), getH());}
    inline TCount getResolution()const
        {return m.size() * getH();}
};
typedef std::shared_ptr<Field> PField;
typedef std::shared_ptr<const Field> PCField;
typedef const Field& CField;

PField initField(const TCoord w, const TCoord h);
PField initField(const TSize& sz);
}
Q_DECLARE_METATYPE(Eng::PField);
