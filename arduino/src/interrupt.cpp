//TODO #2 Check if chair must stop: read digital pin with stop bit from JetSon Nano

#include "interrupt.h"

Interrupt::Interrupt(int interruptPin){
    this->interruptPin = interruptPin;
    return;
}

bool Interrupt::mustStop(){
    // magic ...
    return false;
}