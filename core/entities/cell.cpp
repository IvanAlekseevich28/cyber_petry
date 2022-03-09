#include "cell.h"

using namespace Eng;

Cell::Cell()
{
    clear();
}

void Cell::clear()
{
    arrLiquids.fill(0);
}
