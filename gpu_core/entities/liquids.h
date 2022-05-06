#pragma once
#include <array>
#include <vector>

namespace GEng
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

struct Liquids
{
    std::array<std::vector<int>, LT__END> m;
    std::array<int, LT__END> flowRate;

    inline int size()const {return m[0].size();}
    inline std::vector<int>& operator[] (const size_t i) {return m[i];}

};
}
