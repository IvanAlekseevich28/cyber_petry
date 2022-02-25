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

Cell::Cell() : flow(0,0)
{
    arrLiquids.fill(0);
}

TLiquid Cell::getLiquidsSum() const
{
    TLiquid sum(0);
    for (TCount i = 0; i < LT__END; i++)
        sum += arrLiquids[i];
    return sum;
}

void Cell::applyNeighbourLiquids(const Cell &n, eDirection dir)
{
    for (TCount i = 0; i < LT__END; i++)
    {

    }
}

TFlow Cell::calcGrad(const Cell &last) const
{
    return getLiquidsSum() - last.getLiquidsSum();
}

void Cell::stayLiquids(const Cell &last, TCount cn)
{
    TCount forNeighbours = cn * (last.getLiquidsSum() / 5);
    TCount stay = last.getLiquidsSum() - forNeighbours;

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
