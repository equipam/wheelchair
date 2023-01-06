#include "Led.h"
#include "Arduino.h"

Led::Led(int redPin, int yellowPin, int greenPin, PinInterface* pinInterface)
{
    this->redPin = redPin;
    this->yellowPin = yellowPin;
    this->greenPin = greenPin;
    this->pinInterface = pinInterface;
}


void Led::setup()
{
    pinMode(this->redPin, OUTPUT);
    pinMode(this->yellowPin, OUTPUT);
    pinMode(this->greenPin, OUTPUT);

    this->pinInterface->doDigitalWrite(this->greenPin, HIGH);
    delay(500);
    this->pinInterface->doDigitalWrite(this->yellowPin, HIGH);
    delay(500);
    this->pinInterface->doDigitalWrite(this->redPin, HIGH);
    delay(500);
    this->pinInterface->doDigitalWrite(this->greenPin, LOW);
    this->pinInterface->doDigitalWrite(this->yellowPin, LOW);
    this->pinInterface->doDigitalWrite(this->redPin, LOW);
}


void Led::update(int overwrite)
{

    int ledPin = -1;

    switch (overwrite)
    {
    case 0:
        ledPin = this->greenPin;
        break;
    case 1:
        ledPin = this->yellowPin;
        break;
    case 2:
        ledPin = this->redPin;
        break;
    default:
        break;
    }

    if (ledPin != this->currentHighPin)
    {
        if (this->currentHighPin != -1)
        {
            this->pinInterface->doDigitalWrite(this->currentHighPin, LOW);
        }
        
        this->pinInterface->doDigitalWrite(ledPin, HIGH);
        this->currentHighPin = ledPin;
    }
}
