#include "Chair.h"

Chair::Chair(int vPin, int omegaPin, PinInterface *pinInterface)
{
    this->vPin = vPin;
    this->omegaPin = omegaPin;
    this->pinInterface = pinInterface;
    return;
}

/// @brief Run this to setup chair pins
void Chair::setup()
{
    pinMode(this->vPin, OUTPUT);
    pinMode(this->omegaPin, OUTPUT);
}

void Chair::handleHalt()
{
    if (this->halt)
    {
        // rotate chair?
        while (this->halt)
        {
            PolarCoords rotate = {.v = 0.5, .omega = -90};
            this->pinInterface->doAnalogWrite(this->vPin, Coordinates::map(rotate.v, STANDARDIZED_V_MIN, STANDARDIZED_V_MAX, OUTPUT_V_MIN, OUTPUT_V_MAX));
            this->pinInterface->doAnalogWrite(this->omegaPin, Coordinates::map(rotate.omega, STANDARDIZED_OMEGA_MIN, STANDARDIZED_OMEGA_MAX, OUTPUT_OMEGA_MIN, OUTPUT_OMEGA_MAX));
        }
    }
}

/// @brief Sends a V and Omega command to the chair DB9
/// @param coords Normalized polar coordinates
void Chair::command(PolarCoords coords)
{
    // Procedure to handle halting because of objects in the way
    this->handleHalt();
    // Pass command to chair
    this->pinInterface->doAnalogWrite(this->vPin, Coordinates::map(coords.v, STANDARDIZED_V_MIN, STANDARDIZED_V_MAX, OUTPUT_V_MIN, OUTPUT_V_MAX));
    this->pinInterface->doAnalogWrite(this->omegaPin, Coordinates::map(coords.omega, STANDARDIZED_OMEGA_MIN, STANDARDIZED_OMEGA_MAX, OUTPUT_OMEGA_MIN, OUTPUT_OMEGA_MAX));
    return;
}

void Chair::changeState(bool state)
{
    this->halt = state;
}