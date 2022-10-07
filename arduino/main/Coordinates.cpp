#include "Coordinates.h"

// https://en.wikipedia.org/wiki/Polar_coordinate_system

PolarCoords Coordinates::linearToPolar(LinearCoords coords)
{
    PolarCoords polarCoords = {.v = 0.0 , .omega = 0.0};
    polarCoords.v = sqrt(pow(coords.x,2) + pow(coords.y,2));
    // Saturate magnitude
    polarCoords.v = abs(polarCoords.v) > 1 ? 1 : polarCoords.v;
    polarCoords.omega = atan2(coords.x, coords.y) * RAD_TO_DEG;
    return polarCoords;
}

float Coordinates::map(float value, float fromLow, float fromHigh, float toLow, float toHigh){
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}
