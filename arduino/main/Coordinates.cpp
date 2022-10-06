// TODO: #1 Create function that converts the joystick XY coordinates to Velocity Omega wheelchair input

#include "Coordinates.h"
#include <math.h>

PolarCoords Coordinates::linearToPolar(LinearCoords coords)
{
    PolarCoords polarCoords = {.v = 0.0 , .omega = 0.0};
    polarCoords.v = sqrt(pow(coords.x,2) + pow(coords.y,2)); 
    polarCoords.omega = atan(coords.y / coords.x) * 180/(2*asin(1.0));
    return polarCoords;
}

float Coordinates::map(float value, float fromLow, float fromHigh, float toLow, float toHigh){
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}
