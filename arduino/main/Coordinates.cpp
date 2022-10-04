// TODO: #1 Create function that converts the joystick XY coordinates to Velocity Omega wheelchair input

#include "Coordinates.h"

PolarCoords Coordinates::linearToPolar(LinearCoords coords)
{
    // magic ...
    PolarCoords polarCoords = {.v = 0.0, .omega = 0.0};
    return polarCoords;
}

float Coordinates::map(float value, float fromLow, float fromHigh, float toLow, float toHigh){
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}
