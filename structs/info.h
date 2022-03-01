#pragma once

#include <QMetaType>

namespace Info
{
struct Performance
{
    double  cups=0;   // Cell update per second
    double  fups=0;   // Field update per second
    int     ctis=0;   // Calculation time in seconds
    int     coac=0;   // count of active cores
};

}

Q_DECLARE_METATYPE(Info::Performance);
