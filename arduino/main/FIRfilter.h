#ifndef FIRFILER_H
#define FIRFILER_H

#include <Arduino.h>

struct FIRfilter
{
    const float* x;
    size_t inputLength;
    const float* c;
    size_t filterLength;
    float* y;
    size_t outputLenght;
};

#endif