#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "PinInterface.h"

class Interrupt
{
private:
    int interruptPin;
    PinInterface *pinInterface;

public:
    Interrupt(int interruptPin, PinInterface *pinInterface);
    bool mustStop();
};

#endif
