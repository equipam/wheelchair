#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Coordinates.h"
#include "PinInterface.h"
#include <Stream.h>

#define MIN_X 0
#define MAX_X 3.3
#define MIN_Y 0
#define MAX_X 3.3

#define STANDARDIZED_X_MIN -1
#define STANDARDIZED_X_MAX 1
#define STANDARDIZED_Y_MIN -1
#define STANDARDIZED_Y_MAX 1

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
    int xPin;
    int yPin;
    PinInterface* pinInterface;
public:
    JoystickBounds realBounds;
    Joystick(int xPin, int yPin, PinInterface* pinInterface);
    void calibrate(Stream &io);
    void calibrate_left(Stream &io);
    void calibrate_right(Stream &io);
    void calibrate_front(Stream &io);
    void calibrate_back(Stream &io);
    LinearCoords joystickMapping(LinearCoords realCoords);
    LinearCoords position();
};

#endif
