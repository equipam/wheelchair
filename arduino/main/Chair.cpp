#include "Chair.h"

Chair::Chair(int vPin, int omegaPin, PinInterface *pinInterface)
{
    this->vPin = vPin;
    this->omegaPin = omegaPin;
    this->pinInterface = pinInterface;
    return;
}

void Chair::command(PolarCoords coords)
{
    // TODO #9 Create chair command function
    //  magic...
    return;
}