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


void Led::update(int status)
{
    if (status != this->lastStatus)
    {
        switch (status)
        {
        case 0:
            this->pinInterface->doDigitalWrite(this->greenPin, HIGH);
            this->pinInterface->doDigitalWrite(this->yellowPin, LOW);
            this->pinInterface->doDigitalWrite(this->redPin, LOW);
            break;
        case 1:
            this->pinInterface->doDigitalWrite(this->greenPin, LOW);
            this->pinInterface->doDigitalWrite(this->yellowPin, HIGH);
            this->pinInterface->doDigitalWrite(this->redPin, LOW);
            break;
        case 2:
            this->pinInterface->doDigitalWrite(this->greenPin, LOW);
            this->pinInterface->doDigitalWrite(this->yellowPin, LOW);
            this->pinInterface->doDigitalWrite(this->redPin, HIGH);
            break;
        default:
            break;
        }
    }
    this->lastStatus = status;
}


void Led::warning()
{
    this->pinInterface->doDigitalWrite(this-greenPin, LOW);
    this->pinInterface->doDigitalWrite(this-yellowPin, LOW);
    this->pinInterface->doDigitalWrite(this-redPin, HIGH);
    delay(500);
    this->pinInterface->doDigitalWrite(this-redPin, LOW);
    delay(500);
}