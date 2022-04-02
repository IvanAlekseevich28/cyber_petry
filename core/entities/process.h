#pragma once

#include "field.h"

namespace Eng
{
struct Process
{
    const PCField last;
    PField curr;

    Process(const PCField state) : last(state)
    {
        curr.reset(new Field(*(last)));
    }
};
typedef std::unique_ptr<Process> PProcess;

PProcess startProc(PCField pField);
PField endProc(PProcess fp);
}
