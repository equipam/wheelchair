//TODO #2 Check if chair must stop: read digital pin with stop bit from JetSon Nano

#include "Interrupt.h"

Interrupt::Interrupt(int interruptPin,  PinInterface* pinInterface){
    this->interruptPin = interruptPin;
    this->pinInterface = pinInterface;
    return;
}

bool Interrupt::mustStop(){
    // magic ...
    return false;
}