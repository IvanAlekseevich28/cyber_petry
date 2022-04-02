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
    PField getState();
    PCField getConstState()const;

    void setState(const PField &newPState);

private:
    PField m_pState;
    std::list<PIEngine> m_engines;
};
}
