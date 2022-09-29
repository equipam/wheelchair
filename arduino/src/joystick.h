#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <tuple>
#include "coordinates.h"

#define MIN_X 0
#define MAX_X 3.3
#define MIN_Y 0
#define MAX_X 3.3


struct JoystickBounds
{
    float minX = MIN_X;
    float maxX = MAX_X;
    float minY = MIN_X;
    float maxY = MAX_X;
};


class Joystick
{
private:
    JoystickBounds realBounds;
    int xPin;
    int yPin;
    LinearCoords joystickMapping(LinearCoords realCoords);
public:
    Joystick(int xPin, int yPin);
    void calibrate();
    LinearCoords position();
};

#endif
