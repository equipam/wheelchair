#include "Interrupt.h"

Interrupt::Interrupt(uint8_t interruptPin)
{
    this->interruptPin = interruptPin;
    return;
}

void Interrupt::setup(void (*userFunc)(), int mode)
{
    pinMode(interruptPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(interruptPin), userFunc, mode);
}