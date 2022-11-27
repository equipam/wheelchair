#ifndef PININTERFACE_H
#define PININTERFACE_H

#include <stdint.h>

class PinInterface
{
public:
    virtual void doDigitalWrite(uint8_t pin, uint8_t val);
    virtual int doDigitalRead(uint8_t pin);
    virtual void doAnalogWrite(uint8_t pin, float val);
    virtual float doAnalogRead(uint8_t pin);
};


#endif