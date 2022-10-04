#include "Joystick.h"

Joystick::Joystick(int xPin, int yPin, PinInterface *pinInterface)
{
    this->xPin = xPin;
    this->yPin = yPin;
    this->pinInterface = pinInterface;
    return;
}

void Joystick::calibrate(Stream &io)
{
    // TODO #10 Create joystick calibration function
    //  ask the user to place the joystick in forward, back, left and write positions,
    //  storing the real bounds on the class attribute "realBounds"
}

void Joystick::calibrate_left(Stream &io)
{
    return;
}
void Joystick::calibrate_right(Stream &io)
{
    return;
}
void Joystick::calibrate_front(Stream &io)
{
    return;
}
void Joystick::calibrate_back(Stream &io)
{
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
    pos.y = this->pinInterface->doAnalogRead(this->xPin);
    pos = joystickMapping(pos);
    return pos;
}
