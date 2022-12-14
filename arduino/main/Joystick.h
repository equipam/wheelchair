#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Coordinates.h"
#include "PinInterface.h"
#include "Arduino.h"

#define MIN_X 0
#define MAX_X 5
#define MIN_Y 0
#define MAX_X 5
#define MID_X 0
#define MID_Y 0

#define STANDARDIZED_X_MIN -1
#define STANDARDIZED_X_MAX 1
#define STANDARDIZED_Y_MIN -1
#define STANDARDIZED_Y_MAX 1

#define DEADZONE 0.05

struct JoystickBounds
{
    float minX = MIN_X;
    float maxX = MAX_X;
    float minY = MIN_X;
    float maxY = MAX_X;
    float midX = MID_X;
    float midY = MID_Y;
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
    void setup();
    void calibrate(Stream &io);
    void calibrate_middle();
    bool calibrate_left();
    bool calibrate_right();
    bool calibrate_front();
    bool calibrate_back();
    LinearCoords joystickMapping(LinearCoords realCoords);
    LinearCoords position();
};

#endif
