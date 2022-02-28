#include "types.h"

using namespace Eng;

Flow &Flow::operator+=(const Flow &oth)
{
    xSpd += oth.xSpd;
    ySpd += oth.ySpd;
    return *this;
}

// numerator: 9,5,9,9
Flow Flow::split(TFlow numerator, TFlow denominator, bool sqrt2, bool isLandT)
{
    Flow oth(0,0);
    oth.xSpd = (xSpd * numerator) / denominator;
    oth.ySpd = (ySpd * numerator) / denominator;
    xSpd -= oth.xSpd;
    ySpd -= oth.ySpd;

    if (sqrt2)
    {
        xSpd = (xSpd * 60) / 85; // xSpd / sqrt(2)
        ySpd = (ySpd * 60) / 85; // ySpd / sqrt(2)

        TFlow xTemp = xSpd;
        xSpd += ySpd;
        ySpd += xTemp;
    }

    return oth;
}

Cell::Cell() : irgb(0), sld(0), flow(0,0)
{
    arrLiquids.fill(0);
}

void Cell::clear()
{
    arrLiquids.fill(0);
    irgb = 0;
    sld = 0;
    flow.setXY(0,0);
}

TLiquid Cell::getLiquidsSum() const
{
    TLiquid sum(0);
    for (TCount i = 0; i < LT__END; i++)
        sum += arrLiquids[i];
    return sum;
}

void Cell::applyNeighbourLiquids(const Cell &nbr)
{
    for (TCount i = 0; i < LT__END; i++)
        applyNeighbourLiquid(nbr, (eLiquidType)i);
}

void Cell::stayLiquids(const Cell &last, TCount cn)
{
    for (TCount i = 0; i < LT__END; i++)
        stayLiquid(last, cn, (eLiquidType)i);
}

TCount Cell::getFlowBonus(const Cell &n, eDirection dir, TCount onePart)
{
//    const TCount defVal = onePart;
    switch (dir)
    {
    // x
    case D_right:
    case D_left:
    {
        if (n.flow.xSpd == 0)
            return onePart;

        const TFlow xInertia = n.getLiquidsSum() / n.flow.xSpd;
        TFlow xBonus = (xInertia != 0 ? onePart / xInertia : onePart);
        if (dir == D_left) return onePart + xBonus;
        else return onePart - xBonus;
    }
        // y
        case D_top:
        case D_bottom:
        {
            if (n.flow.ySpd == 0)
                return onePart;

            const TFlow yInertia = n.getLiquidsSum() / n.flow.ySpd;
            TFlow yBonus = (yInertia != 0 ? onePart / yInertia : onePart);
            if (dir == D_bottom) return onePart + yBonus;
            else return onePart - yBonus;
        }
    default:
        return onePart;
    }
}

eDirection Point::getRelativelyDirection(const Point &o) const
{
    const TFlow rX = o.x - x;
    const TFlow rY = o.y - y;

    if (rX > 0) return D_right;
    if (rX < 0) return D_left;
    if (rY > 0) return D_top;
    if (rY < 0) return D_bottom;

    return D_none;
//    eDirection dir(D_none);
//    if (rX > 0) dir = D_left;
//    else if (rX < 0) dir = D_right;
//    if (rY> 0) dir = D_top;
//    else if (rY < 0) dir = D_bottom;

//    return dir;
}

DirPoint::DirPoint(TCoord x, TCoord y, eDirection direction) : p(x,y), direct(direction)
{

}

SimParams::SimParams(bool hasAllLiquids, bool hasSolid, bool hasLights, bool hasHeat, bool hasFlow) :
    hasAllLiquids(hasAllLiquids), hasSolid(hasSolid), hasLights(hasLights), hasHeat(hasHeat), hasFlow(hasFlow) {}
