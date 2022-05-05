#pragma once

#include "../entities/liquids.h"
#include <memory>
#include <optional>


using OptLiquids = std::optional<Liquids>;
using COptLiquids = const OptLiquids&;


Liquids initLiquids(const int defValue = 0);
