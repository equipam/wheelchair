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

class Chair
{
private:
    int vPin;
    int omegaPin;
    int switchPin;
    float speeds[3] = {0.1, 0.5, 1.0};
    int currentSpeed = 0;
    int lastSwitchState=0;
    PinInterface *pinInterface;
    bool halt = false;
    // void handleHalt(PolarCoords coords);
public:
    Chair(int vPin, int omegaPin, int switchPin, PinInterface *pinInterface);
    void setup();
    void command(LinearCoords coords);
    void setHalt(bool state);
    void changeSpeed();
    float safetyBounds(float input);
};

#endif