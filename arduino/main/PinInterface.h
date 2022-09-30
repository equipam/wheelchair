#ifndef PININTERFACE_H
#define PININTERFACE_H

#include <stdint.h>

class PinInterface {
public:
    virtual void doDigitalWrite(uint8_t pin, uint8_t val);
    virtual int doDigitalRead(uint8_t pin);
    virtual void doAnalogWrite(uint8_t pin, int val);
    virtual int doAnalogRead(uint8_t pin);
};

class RealPinInterface: public PinInterface{
public:
    void doDigitalWrite(uint8_t pin, uint8_t val);
    int doDigitalRead(uint8_t pin);
    void doAnalogWrite(uint8_t pin, int val);
    int doAnalogRead(uint8_t pin);
};

#endif