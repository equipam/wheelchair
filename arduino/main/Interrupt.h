#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <Arduino.h>

class Interrupt
{
private:
    uint8_t interruptPin;

public:
    Interrupt(uint8_t interruptPin);
    void setup(void (*userFunc)(), int mode);
};

#endif
