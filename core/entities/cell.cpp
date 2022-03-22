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

void Cell::clear()
{
    arrLiquids.fill(0);
    wave  = 0;
    wave1 = 0;
    wave2 = 0;
}
