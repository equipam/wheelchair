#if !defined(REALPININTERFACE_H)
#define REALPININTERFACE_H

#include "PinInterface.h"
#include "Arduino.h"

#define ANALOG_RESOLUTION 5 / 1023

class RealPinInterface : public PinInterface
{
public:
    void doDigitalWrite(uint8_t pin, uint8_t val);
    int doDigitalRead(uint8_t pin);
    void doAnalogWrite(uint8_t pin, float val);
    float doAnalogRead(uint8_t pin);
};

#endif // REALPININTERFACE_H
