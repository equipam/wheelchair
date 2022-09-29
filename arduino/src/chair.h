#ifndef CHAIR_H
#define CHAIR_H

#include "coordinates.h"

class Chair
{
private:
    int vPin;
    int omegaPin;
public:
    Chair(int vPin, int omegaPin);
    void command(PolarCoords coords);
};


#endif