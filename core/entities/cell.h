#pragma once

#include <array>
#include <QMetaType>

namespace Eng
{
enum eLiquidType
{
    LT_water,
    LT_oxygen,
    LT_carbon,
    LT_nitrogen,
    LT_acid,
    LT_organic,

    LT__END
};

typedef int TLiquid;
typedef int TWave;
typedef unsigned TCount;
typedef std::array<TLiquid, LT__END> TLiquids;

struct Cell
{
    TLiquids arrLiquids;

    TWave wave; // rendered wave
    TWave wave1;
    TWave wave2;

    Cell();
    Cell(const Cell& oth);
    Cell operator+(const Cell& oth)const;
    Cell& operator+=(const Cell& oth);
    void clear();
    TLiquid countLiquids()const;

};
typedef const Cell& CCell;
}

Q_DECLARE_METATYPE(Eng::Cell);
