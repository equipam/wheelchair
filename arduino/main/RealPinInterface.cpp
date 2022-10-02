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

void RealPinInterface::doAnalogWrite(uint8_t pin, float val)
{
    int realVal = static_cast<int>(val / ANALOG_RESOLUTION);
    analogWrite(pin, val);
}

float RealPinInterface::doAnalogRead(uint8_t pin)
{
    return static_cast<float>(analogRead(pin) * ANALOG_RESOLUTION);
}