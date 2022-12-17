#include "Chair.h"

Chair::Chair(int vPin, int omegaPin, int switchPin, PinInterface *pinInterface)
{
    this->vPin = vPin;
    this->omegaPin = omegaPin;
    this->switchPin = switchPin;
    this->pinInterface = pinInterface;
    return;
}

/// @brief Run this to setup chair pins
void Chair::setup()
{
    pinMode(this->vPin, OUTPUT);
    pinMode(this->omegaPin, OUTPUT);
    pinMode(this->switchPin, INPUT_PULLUP);
}


void Chair::changeSpeed()
{
    // The pin is 1 when the switch is off, hence the "not"
    int result = !this->pinInterface->doDigitalRead(this->switchPin);

    if(result && !this->lastSwitchState)
    {
        this->currentSpeed++;
        if(this->currentSpeed >= SPEEDS)
        {
            this->currentSpeed = 0;
        }
    }
    this->lastSwitchState = result;
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

float Chair::safetyBounds(float input)
{
    float biased = input - 0.06;
    if (biased > 2.0)
        return 2.0;
    if (biased < 1.2)
        return 1.2;
    return biased;
}


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
    /*float outputVDelta = OUTPUT_V_MAX - OUTPUT_V_MIN;
    float avgOutputV = (OUTPUT_V_MAX + OUTPUT_V_MIN) / 2;
    float output_v_min = avgOutputV - outputVDelta/2 * this->speeds[this->currentSpeed];
    float output_v_max = avgOutputV + outputVDelta/2 * this->speeds[this->currentSpeed];

    float outputOmegaDelta = OUTPUT_V_MAX - OUTPUT_V_MIN;
    float avgOutputOmega = (OUTPUT_V_MAX + OUTPUT_V_MIN) / 2;
    float output_omega_min = avgOutputOmega - outputOmegaDelta/2 * this->speeds[this->currentSpeed];
    float output_omega_max = avgOutputOmega + outputOmegaDelta/2 * this->speeds[this->currentSpeed];

    float mappedX = Coordinates::map(command.x, STANDARDIZED_V_MIN, STANDARDIZED_V_MAX, output_v_min, output_v_max);
    float mappedY = Coordinates::map(command.y, STANDARDIZED_OMEGA_MIN,
    STANDARDIZED_OMEGA_MAX, output_omega_min, output_omega_max);*/

    // apply deadband
    command.x = abs(command.x)<DEADBAND ? 0 : command.x;
    command.y = abs(command.y)<DEADBAND ? 0 : command.y;

    command.x = command.x * this->speeds[this->currentSpeed];
    command.y = command.y * this->speeds[this->currentSpeed];
    
    float mappedX = Coordinates::map(command.x, STANDARDIZED_V_MIN, STANDARDIZED_V_MAX, OUTPUT_V_MIN, OUTPUT_V_MAX);
    float mappedY = Coordinates::map(command.y, STANDARDIZED_OMEGA_MIN, STANDARDIZED_OMEGA_MAX, OUTPUT_OMEGA_MIN, OUTPUT_OMEGA_MAX);

    float finalX = this->safetyBounds(mappedX);
    float finalY = this->safetyBounds(mappedY);
    Serial.print(finalX);
    Serial.print(" | ");
    Serial.println(finalY);
    // Pass command to chair
    this->pinInterface->doAnalogWrite(this->vPin, finalX);
    this->pinInterface->doAnalogWrite(this->omegaPin, finalY);
    return;
}

void Chair::setHalt(bool state)
{
    this->halt = state;
}