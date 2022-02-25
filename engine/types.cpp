#include "types.h"

using namespace Eng;

Flow &Flow::operator+=(const Flow &oth)
{
    xSpd += oth.xSpd;
    ySpd += oth.ySpd;
    return *this;
}

// numerator: 9,5,9,9
Flow Flow::split(TFlow numerator, TFlow denominator, bool sqrt2)
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
