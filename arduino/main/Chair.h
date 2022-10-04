#ifndef CHAIR_H
#define CHAIR_H

#include "Coordinates.h"
#include "PinInterface.h"
#include "Arduino.h"

#define STANDARDIZED_V_MIN 0
#define STANDARDIZED_V_MAX 1
#define STANDARDIZED_OMEGA_MIN -180
#define STANDARDIZED_OMEGA_MAX 180

#define OUTPUT_V_MIN 0
#define OUTPUT_V_MAX 3.3
#define OUTPUT_OMEGA_MIN 0
#define OUTPUT_OMEGA_MAX 3.3

class Chair
{
private:
    int vPin;
    int omegaPin;
    PinInterface *pinInterface;
    bool halt = false;
    void handleHalt();
public:
    Chair(int vPin, int omegaPin, PinInterface *pinInterface);
    void setup();
    void command(PolarCoords coords);
    void setHalt(bool state);
};

#endif