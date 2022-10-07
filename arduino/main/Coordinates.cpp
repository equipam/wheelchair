#include "Coordinates.h"
#include <math.h>

// https://en.wikipedia.org/wiki/Polar_coordinate_system



float atan2(float x, float y)
{
    if(x > 0) return atan(y/x);
    else if(x < 0 && y >= 0) return atan(y/x) + PI;
    else if(x < 0 && y < 0) return atan(y/x) - PI;
    else if(x = 0 && y > 0) return HALF_PI;
    else if(x = 0 && y < 0) return -HALF_PI;
    // Else, it's not defined...
    return 0.0;
}

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
