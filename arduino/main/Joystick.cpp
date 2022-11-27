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

void Joystick::calibrate(Stream &io)
{
    io.write("Don't touch the joystick. Press any key");
    while(io.read()==-1){}
    calibrate_middle();
    io.write("Place the joystick forward. Press any key");
    while(io.read()==-1){}
    calibrate_front();
    io.write("Place the joystick back. Press any key");
    while(io.read()==-1){}
    calibrate_back();
    io.write("Place the joystick left. Press any key");
    while(io.read()==-1){}
    calibrate_left();
    io.write("Place the joystick right. Press any key");
    while(io.read()==-1){}
    calibrate_right();
}

void Joystick::calibrate_middle()
{
    this->realBounds.midX = this->pinInterface->doAnalogRead(this->xPin);
    this->realBounds.midY = this->pinInterface->doAnalogRead(this->yPin);
    return;
}
bool Joystick::calibrate_left()
{
    float xRead = this->pinInterface->doAnalogRead(this->xPin);
    float yRead = this->pinInterface->doAnalogRead(this->yPin);
    float realValue;

    if(xRead > 1.1*this->realBounds.midX || xRead < 0.9*this->realBounds.midX)
    {
        realValue = xRead;
    }
    else if(yRead > 1.1*this->realBounds.midY || yRead < 0.9*this->realBounds.midY)
    {
        realValue = yRead;
    }
    else
    {
        return false;
    }

    this->realBounds.minX = realValue;
    return true;
}

bool Joystick::calibrate_right()
{   
    float xRead = this->pinInterface->doAnalogRead(this->xPin);
    float yRead = this->pinInterface->doAnalogRead(this->yPin);
    float realValue;

    if(xRead > 1.1*this->realBounds.midX || xRead < 0.9*this->realBounds.midX)
    {
        realValue = xRead;
    }
    else if(yRead > 1.1*this->realBounds.midY || yRead < 0.9*this->realBounds.midY)
    {
        realValue = yRead;
    }
    else
    {
        return false;
    }
    this->realBounds.maxX = realValue;
    return true;
}

bool Joystick::calibrate_front()
{   
    float xRead = this->pinInterface->doAnalogRead(this->xPin);
    float yRead = this->pinInterface->doAnalogRead(this->yPin);
    float realValue;

    if(xRead > 1.1*this->realBounds.midX || xRead < 0.9*this->realBounds.midX)
    {
        realValue = xRead;
    }
    else if(yRead > 1.1*this->realBounds.midY || yRead < 0.9*this->realBounds.midY)
    {
        realValue = yRead;
    }
    else
    {
        return false;
    }
    this->realBounds.maxY = realValue;
    return true;
}

bool Joystick::calibrate_back()
{
    float xRead = this->pinInterface->doAnalogRead(this->xPin);
    float yRead = this->pinInterface->doAnalogRead(this->yPin);
    float realValue;

    if(xRead > 1.1*this->realBounds.midX || xRead < 0.9*this->realBounds.midX)
    {
        realValue = xRead;
    }
    else if(yRead > 1.1*this->realBounds.midY || yRead < 0.9*this->realBounds.midY)
    {
        realValue = yRead;
    }
    else
    {
        return false;
    }
    this->realBounds.minY = realValue;
    return true;
}

/// @brief Map the joystick coordinates to standardized range
/// @param realCoords
/// @return Coordinates in standardized range
LinearCoords Joystick::joystickMapping(LinearCoords realCoords)
{
    LinearCoords normalizedCoords;
    normalizedCoords.x = Coordinates::map(realCoords.x, realBounds.minX, realBounds.maxX, STANDARDIZED_X_MIN, STANDARDIZED_X_MAX);
    normalizedCoords.y = Coordinates::map(realCoords.y, realBounds.minY, realBounds.maxY, STANDARDIZED_Y_MIN, STANDARDIZED_Y_MAX);

    normalizedCoords.x = normalizedCoords.x < STANDARDIZED_X_MIN ? STANDARDIZED_X_MIN : normalizedCoords.x;
    normalizedCoords.x = normalizedCoords.x > STANDARDIZED_X_MAX ? STANDARDIZED_X_MAX : normalizedCoords.x;
    normalizedCoords.y = normalizedCoords.y < STANDARDIZED_Y_MIN ? STANDARDIZED_Y_MIN : normalizedCoords.y;
    normalizedCoords.y = normalizedCoords.y > STANDARDIZED_Y_MAX ? STANDARDIZED_Y_MAX : normalizedCoords.y;

    return normalizedCoords;
}

LinearCoords Joystick::position()
{
    LinearCoords pos;
    pos.x = this->pinInterface->doAnalogRead(this->xPin);
    pos.y = this->pinInterface->doAnalogRead(this->yPin);
    pos = joystickMapping(pos);
    if(abs(pos.x) < DEADZONE) pos.x = 0;
    if(abs(pos.y) < DEADZONE) pos.y = 0;
    return pos;
}
