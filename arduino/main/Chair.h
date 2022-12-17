#ifndef CHAIR_H
#define CHAIR_H

#include "Coordinates.h"
#include "PinInterface.h"
#include "Arduino.h"

#define STANDARDIZED_V_MIN -1
#define STANDARDIZED_V_MAX 1
#define STANDARDIZED_OMEGA_MIN -1
#define STANDARDIZED_OMEGA_MAX 1

#define OUTPUT_V_MIN 0
#define OUTPUT_V_MAX 3.3
#define OUTPUT_OMEGA_MIN 0
#define OUTPUT_OMEGA_MAX 3.3

#define SPEEDS 3

#define DEADBAND 0.05

class Chair
{
private:
    int vPin;
    int omegaPin;
    int switchPin;
    float speeds[SPEEDS] = {0.1, 0.2, 0.5};
    int lastSwitchState=0;
    PinInterface *pinInterface;
    bool halt = false;
    // void handleHalt(PolarCoords coords);
public:
    int currentSpeed = 0;
    Chair(int vPin, int omegaPin, int switchPin, PinInterface *pinInterface);
    void setup();
    void command(LinearCoords coords);
    void setHalt(bool state);
    void changeSpeed();
    float safetyBounds(float input);
};

#endif