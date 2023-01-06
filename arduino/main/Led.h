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
    int currentHighPin = -1;
    Led(int redPin, int yellowPin, int greenPin, PinInterface* pinInterface);
    void setup();
    void update(int overwrite);
};


#endif // LED_H