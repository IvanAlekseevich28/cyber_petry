#pragma once

#include "../entities/process.h"

namespace Eng
{
class IEngine
{
public:
    virtual PProcess step(PProcess proc, const TCount countThreads=1) = 0;
};
typedef std::unique_ptr<IEngine> PIEngine;
}
