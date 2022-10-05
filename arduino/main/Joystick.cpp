#include "Joystick.h"


Joystick::Joystick(int xPin, int yPin, PinInterface *pinInterface)
{
    this->xPin = xPin;
    this->yPin = yPin;
    this->pinInterface = pinInterface;
    return;
}

/// @brief Run this to setup joystick pins
void Joystick::setup()
{
    pinMode(this->xPin, INPUT);
    pinMode(this->yPin, INPUT);
}

void Joystick::calibrate_middle()
{
    this->realBounds.midX = this->pinInterface->doAnalogRead(this->xPin);
    this->realBounds.midY = this->pinInterface->doAnalogRead(this->yPin); 
    return;
}
void Joystick::calibrate_left()
{
    
    this->realBounds.minX = this->pinInterface->doAnalogRead(this->xPin);
    return;
}
void Joystick::calibrate_right()
{   
    this->realBounds.maxX = this->pinInterface->doAnalogRead(this->xPin);
    return;
}
void Joystick::calibrate_front()
{   
    
    this->realBounds.maxY = this->pinInterface->doAnalogRead(this->yPin);
    return;
}

void Joystick::calibrate_back()
{
    
    this->realBounds.minY = this->pinInterface->doAnalogRead(this->yPin);
    return;
}

/// @brief Map the joystick coordinates to standardized range
/// @param realCoords
/// @return Coordinates in standardized range
LinearCoords Joystick::joystickMapping(LinearCoords realCoords)
{
    LinearCoords normalizedCoords;
    normalizedCoords.x = Coordinates::map(realCoords.x, realBounds.minX, realBounds.maxX, STANDARDIZED_X_MIN, STANDARDIZED_X_MAX);
    normalizedCoords.y = Coordinates::map(realCoords.y, realBounds.minY, realBounds.maxY, STANDARDIZED_Y_MIN, STANDARDIZED_Y_MAX);
    return normalizedCoords;
}

LinearCoords Joystick::position()
{
    LinearCoords pos;
    pos.x = this->pinInterface->doAnalogRead(this->xPin);
    pos.y = this->pinInterface->doAnalogRead(this->yPin);
    pos = joystickMapping(pos);
    return pos;
}
