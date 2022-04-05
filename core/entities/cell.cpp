#include "cell.h"

using namespace Eng;

Cell::Cell()
{
    clear();
}

Cell::Cell(const Cell &oth) :
    arrLiquids(oth.arrLiquids), wave(oth.wave),
    wave1(oth.wave1), wave2(oth.wave2)
{}

Cell Cell::operator+(const Cell &oth) const
{
    Cell nc;
    nc.clear();

    for (int i = 0; i< LT__END; i++)
        nc.arrLiquids[i] = this->arrLiquids[i] + oth.arrLiquids[i];

    nc.wave = this->wave + oth.wave;
    nc.wave1 = this->wave1 + oth.wave1;
    nc.wave2 = this->wave2 + oth.wave2;

    return nc;
}

Cell &Cell::operator+=(const Cell &oth)
{
    for (int i = 0; i< LT__END; i++)
        arrLiquids[i] += oth.arrLiquids[i];

    wave += oth.wave;
    wave1 += oth.wave1;
    wave2 += oth.wave2;

    return *this;
}

void Cell::clear()
{
    arrLiquids.fill(0);
    wave  = 0;
    wave1 = 0;
    wave2 = 0;
}

TLiquid Cell::countLiquids() const
{
    return std::accumulate(arrLiquids.begin(), arrLiquids.end(), 0);
}
