#pragma once

namespace Draw
{
// Look for Eng::eFluidTypes

//enum eLiquidType
//{
//    LT_water,
//    LT_oxygen,
//    LT_carbon,
//    LT_nitrogen,
//    LT_acid,
//    LT_organic,

//    LT__END
//};
enum eDrawObjects
{
    DO_none,
    DO_water    =0x01,
    DO_oxygen   =0x02,
    DO_carbon   =0x04,
    DO_nitrogen =0x08,
    DO_acid     =0x10,
    DO_organic  =0x20,

    DO__All = 0xffffffff
};

}
