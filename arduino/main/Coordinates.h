#ifndef COORDINATES_H
#define COORDINATES_H

struct LinearCoords
{
    float x;
    float y;
};

struct PolarCoords
{
    float v;
    float omega;
};

class Coordinates
{
public:
    static PolarCoords linearToPolar(LinearCoords coords);
    static float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
};

#endif