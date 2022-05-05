#ifndef FIELD_H
#define FIELD_H

#include "liquids.h"

typedef struct // Field
{
    Liquids* arrLiquids;
    Liquids  flowRate;
    int width;
    int height;
} Field;

#endif // FIELD_H
