// TODO #2 Check if chair must stop: read digital pin with stop bit from JetSon Nano

#include "Interrupt.h"

Interrupt::Interrupt(int interruptPin, PinInterface *pinInterface)
{
    this->interruptPin = interruptPin;
    this->pinInterface = pinInterface;
    return;
}

bool Interrupt::mustStop()
{
    if(this->pinInterface->doDigitalRead(this->interruptPin) == 1)
        return true;
    else return false;
    
}