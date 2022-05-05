#pragma once

#include "liquids.h"
#include "../entities/field.h"
#include "../../structs/size.h"

using PField = std::shared_ptr<Field>;
using OptLiquids = std::optional<Liquids>;
using COptLiquids = const OptLiquids&;

PField initField(const TSize size, OptLiquids initLiquids = {}, OptLiquids flowRate = {});
void deleteField(PField pField);
