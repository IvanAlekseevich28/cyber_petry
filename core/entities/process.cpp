#include "process.h"

namespace Eng
{
PProcess startProc(PCField pField)
{
    PProcess fp(new Process(pField));

    return fp;
}

PField endProc(PProcess fp)
{
    PField answ(move(fp->curr));
    fp.reset();

    return answ;
}
}
