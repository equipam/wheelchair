#ifndef COORDINATES_H
#define COORDINATES_H

#include <math.h>

struct LinearCoords
{
    float x;
    float y;
};


class Coordinates
{
public:
    static float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
};

#endif