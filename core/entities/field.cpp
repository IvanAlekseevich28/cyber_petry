#include "field.h"

namespace Eng
{
Field::Field(const TCoord w, const TCoord h) :
    index(0)
{
    m.resize(w);
    for (int i = 0; i < w; i++)
        m[i].resize(h);

    flowsRate.fill(5);
    flowsRate[LT_acid] = 4*5;
    flowsRate[LT_nitrogen] = 2*5;
    flowsRate[LT_carbon] = 32*5;
    flowsRate[LT_organic] = 16*5;

    wavePowerLosingPow2 = 8;
}

Field::Field(const Field &oth) :
    m(oth.m), flowsRate(oth.flowsRate),
    wavePowerLosingPow2(oth.wavePowerLosingPow2), index(oth.index + 1) {}

bool Field::inField(CPoint p) const
{
    if ((unsigned)p.x < m.size() && (unsigned)p.y < getH())
        return true;
    return false;
}

Points Field::getNeighbours(CPoint p) const
{
    Points lst;
    if (p.x != (TCoord)m.size()-1)      lst.emplace_back(p.x+1, p.y);
    if (p.x != 0)                       lst.emplace_back(p.x-1, p.y);
    if (p.y != (TCoord)m[0].size()-1)   lst.emplace_back(p.x, p.y+1);
    if (p.y != 0)                       lst.emplace_back(p.x, p.y-1);

    return lst;
}

TCount Field::getMatrixLen() const
{
    return m.size() * m[0].size();
}
PField initField(const TSize &sz)
{
    return initField(sz.w, sz.h);
}

PField initField(const TCoord w, const TCoord h)
{
    return PField(new Field(w,h));
}
}
