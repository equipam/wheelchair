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

// void Chair::handleHalt(PolarCoords coords)
// {
//     if (this->halt && coords.omega > -30 && coords.omega < 30)
//     {
//         // rotate chair?
//         while (this->halt)
//         {
//             PolarCoords rotate = {.v = 0.5, .omega = -90};
//             this->pinInterface->doAnalogWrite(this->vPin, Coordinates::map(rotate.v, STANDARDIZED_V_MIN, STANDARDIZED_V_MAX, OUTPUT_V_MIN, OUTPUT_V_MAX));
//             this->pinInterface->doAnalogWrite(this->omegaPin, Coordinates::map(rotate.omega, STANDARDIZED_OMEGA_MIN, STANDARDIZED_OMEGA_MAX, OUTPUT_OMEGA_MIN, OUTPUT_OMEGA_MAX));
//         }
//     }
// }

/// @brief Sends a V and Omega command to the chair DB9
/// @param coords Normalized polar coordinates
void Chair::command(LinearCoords coords)
{
    
    // Don't send command to chair if halt and coords mean to go "forward"
    LinearCoords command = coords;
    if (this->halt && coords.x > -30 && coords.y < 30)
    {
        command.x = 0;
        command.y = 0;
    }

    // Use this to dance :)
    // this->handleHalt(coords)

    float mappedX = Coordinates::map(coords.x, STANDARDIZED_V_MIN, STANDARDIZED_V_MAX, OUTPUT_V_MIN, OUTPUT_V_MAX);
    float mappedY = Coordinates::map(coords.y, STANDARDIZED_OMEGA_MIN, STANDARDIZED_OMEGA_MAX, OUTPUT_OMEGA_MIN, OUTPUT_OMEGA_MAX);

    // Pass command to chair
    this->pinInterface->doAnalogWrite(this->vPin, mappedX);
    this->pinInterface->doAnalogWrite(this->omegaPin, mappedY);
    return;
}

void Chair::setHalt(bool state)
{
    this->halt = state;
}