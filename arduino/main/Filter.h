#ifndef FILTER_H
#define FILTER_H

#include <Arduino.h>
#include "Coordinates.h"

/*
struct FIRfilter
{
    const float *x;
    size_t inputLength;
    const float *c;
    size_t filterLength;
    float *y;
    size_t outputLenght;
};
*/

class Filter
{
public:
    Filter();
    LinearCoords apply(LinearCoords input);
};

#endif