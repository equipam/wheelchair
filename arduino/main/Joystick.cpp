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

LinearCoords Joystick::joystickMapping(LinearCoords realCoords)
{
    /// @brief Map the joystick coordinates to standardized range
    /// @param realCoords
    /// @return Coordinates in standardized range
    /* To map
        [A, B] --> [a, b]
        use this formula
        (val - A)*(b-a)/(B-A) + a */
    LinearCoords normalizedCoords;
    normalizedCoords.x = (realCoords.x - realBounds.minX)*(STANDARDIZED_X_MAX-STANDARDIZED_X_MIN)/(realBounds.maxX-realBounds.minX) + STANDARDIZED_X_MIN;
    normalizedCoords.y = (realCoords.y - realBounds.minY)*(STANDARDIZED_Y_MAX-STANDARDIZED_Y_MIN)/(realBounds.maxY-realBounds.minY) + STANDARDIZED_Y_MIN;
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
