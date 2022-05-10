#pragma once

#include "liquids.h"
#include "../../structs/size.h"
#include <memory>

namespace GEng
{
struct Field
{
    const int index;
    TSize size;
    Liquids arrLiquids;

    Field(TSize s, int index);
};

using PField = std::shared_ptr<Field>;
using PCField = std::shared_ptr<const Field>;
}
