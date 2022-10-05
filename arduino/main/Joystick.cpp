#include "Joystick.h"


Joystick::Joystick(int xPin, int yPin, PinInterface *pinInterface)
{
    this->xPin = xPin;
    this->yPin = yPin;
    this->pinInterface = pinInterface;
    return;
}
    // TODO #10 Create joystick calibration function
    //  ask the user to place the joystick in forward, back, left and write positions,
    //  storing the real bounds on the class attribute "realBounds"

void Joystick::calibrate_middle(Stream &io) 
{

    this->realBounds.midX = this->pinInterface->doAnalogRead(this->xPin);
    this->realBounds.midY = this->pinInterface->doAnalogRead(this->yPin); 
    return;
}
void Joystick::calibrate_left(Stream &io)
{
    
    this->realBounds.minX = this->pinInterface->doAnalogRead(this->xPin);
    return;
}
void Joystick::calibrate_right(Stream &io)
{   
    
    this->realBounds.maxX = this->pinInterface->doAnalogRead(this->xPin);
    return;
}
void Joystick::calibrate_front(Stream &io)
{   
    
    this->realBounds.maxY = this->pinInterface->doAnalogRead(this->yPin);
    return;
}

void Joystick::calibrate_back(Stream &io)
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
