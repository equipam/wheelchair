#ifndef CHAIR_H
#define CHAIR_H

#include "Coordinates.h"
#include "PinInterface.h"

#define STANDARDIZED_V_MIN -1
#define STANDARDIZED_V_MAX 1
#define STANDARDIZED_OMEGA_MIN -1
#define STANDARDIZED_OMEGA_MAX 1

class Chair
{
private:
    int vPin;
    int omegaPin;
    PinInterface *pinInterface;

public:
    Chair(int vPin, int omegaPin, PinInterface *pinInterface);
    void command(PolarCoords coords);
};

#endif