#pragma once

#include "field.h"

namespace Eng
{
struct Process
{
    const PField last;
    PField curr;

    Process(const PField state) : last(state)
    {
        curr.reset(new Field(*(last)));
    }
};
typedef std::unique_ptr<Process> PProcess;

PProcess startProc(PField pField);
PField endProc(PProcess fp);
}
