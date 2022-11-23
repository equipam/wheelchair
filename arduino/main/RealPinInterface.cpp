#include "Arduino.h"
#include "PinInterface.h"

void RealPinInterface::doDigitalWrite(uint8_t pin, uint8_t val)
{
    digitalWrite(pin, val);
}

int RealPinInterface::doDigitalRead(uint8_t pin)
{
    return digitalRead(pin);
}

/// @brief Analog Write
/// @param pin Pin number
/// @param val Value between 0 and 3.3 to write
void RealPinInterface::doAnalogWrite(uint8_t pin, float val)
{
    float finalVal = val;
    if(val < 0) finalVal = 0;
    if(val > 3.3) finalVal = 3.3;
    int realVal = static_cast<int>(finalVal * 3.3/255);
    analogWrite(pin, realVal);
}

/// @brief Analog Read
/// @param pin Pin number
/// @return Value between 0 and 3.3 (V)
float RealPinInterface::doAnalogRead(uint8_t pin)
{
    return static_cast<float>(analogRead(pin)) * ANALOG_RESOLUTION;
}