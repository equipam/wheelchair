#include "Chair.h"

Chair::Chair(int vPin, int omegaPin, PinInterface *pinInterface)
{
    this->vPin = vPin;
    this->omegaPin = omegaPin;
    this->pinInterface = pinInterface;
    return;
}

void Chair::command(PolarCoords coords)   //Chair command function
{
    this->pinInterface->doAnalogWrite(this->vPin, map(coords.v,STANDARDIZED_V_MIN,STANDARDIZED_V_MAX,OUTPUT_V_MIN,OUTPUT_V_MAX));
    this->pinInterface->doAnalogWrite(this->omegaPin, map(coords.omega,STANDARDIZED_OMEGA_MIN,STANDARDIZED_OMEGA_MAX,OUTPUT_OMEGA_MIN,OUTPUT_OMEGA_MAX));
    return;
}