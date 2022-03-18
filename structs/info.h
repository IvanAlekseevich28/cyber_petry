#pragma once

#include <QMetaType>

namespace Info
{
struct Performance
{
    double  cups=0;   // Cell update per second
    double   ups=0;   // Field update per second
    double   fps=0;   // frames per second
    int     ctis=0;   // Calculation time in seconds
    int     coac=0;   // count of active cores
};


}

Q_DECLARE_METATYPE(Info::Performance);
