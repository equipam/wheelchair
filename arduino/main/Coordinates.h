#ifndef COORDINATES_H
#define COORDINATES_H

#include <Arduino.h>
#include <math.h>

struct LinearCoords
{
    float x;
    float y;
};

struct ChairCoords
{
    float v;
    float omega;
};

class Coordinates
{
public:
    //static PolarCoords linearToPolar(LinearCoords coords);
    static float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
};

#endif