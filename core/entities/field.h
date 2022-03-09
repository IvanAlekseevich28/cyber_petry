#pragma once

#include "cell.h"
#include "point.h"
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

    const unsigned index;

    explicit Field(const TCoord w, const TCoord h);
    explicit Field(const Field& oth);

    bool inField(CPoint p)const;
    Points getNeighbours(CPoint p)const;
    TCount getMatrixLen()const;
    inline TCount getH()const
        {return m[0].size();}
};
typedef std::shared_ptr<Field> PField;
typedef const Field& CField;

PField initField(const TCoord w, const TCoord h);
}
Q_DECLARE_METATYPE(Eng::PField);
