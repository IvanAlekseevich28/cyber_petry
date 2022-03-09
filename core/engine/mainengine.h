#pragma once

#include <list>
#include "IEngine.h"

namespace Eng
{
class MainEngine
{
public:
    MainEngine(PField state);
    const PField step(const TCount countThreads=1);
    PField getState()const;

private:
    PField m_pState;
    std::list<PIEngine> m_engines;
};
}
