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
    //opcção interessante usar a função map() de arduino
    
    PolarCoords normalizeCoords;
    normalizeCoords.v=(coords.v + 1) * 3.3 / 2;             
    normalizeCoords.omega=(coords.omega + 1) * 3.3 / 2;

    this->pinInterface->doAnalogWrite(this->vPin, normalizeCoords.v/5*255);
    this->pinInterface->doAnalogWrite(this->omegaPin, normalizeCoords.omega/5*255);

    // TODO #9 Create chair command function - Check
    
    return;
}