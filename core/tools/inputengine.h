#pragma once

#include "fieldtools.h"
#include "../entities/poscell.h"

namespace Eng
{
class InputEngine
{
public:
    InputEngine(PField pFld);
    bool input(PField pFld);
    void reset();

private:
    int m_processedIndex;
    FieldTools m_tool;
};
}
