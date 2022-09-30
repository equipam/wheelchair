#ifndef CHAIR_H
#define CHAIR_H

#include "Coordinates.h"
#include "PinInterface.h"

class Chair
{
private:
    int vPin;
    int omegaPin;
    PinInterface* pinInterface;
public:
    Chair(int vPin, int omegaPin, PinInterface* pinInterface);
    void command(PolarCoords coords);
};


#endif