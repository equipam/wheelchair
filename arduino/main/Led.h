#ifndef LED_H
#define LED_H

#include "PinInterface.h"

class Led
{
private:
    int redPin;
    int yellowPin;
    int greenPin;
    PinInterface* pinInterface;
public:
    int lastStatus = -1;
    Led(int redPin, int yellowPin, int greenPin, PinInterface* pinInterface);
    void setup();
    void update(int status);
    void warning();
};


#endif // LED_H