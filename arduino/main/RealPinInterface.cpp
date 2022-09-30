#include "Arduino.h"
#include "PinInterface.h"


void RealPinInterface::doDigitalWrite(uint8_t pin, uint8_t val) {
    digitalWrite(pin, val);
}
int RealPinInterface::doDigitalRead(uint8_t pin) {
    return digitalRead(pin);
}
void RealPinInterface::doAnalogWrite(uint8_t pin, int val) {
    analogWrite(pin, val);
}
int RealPinInterface::doAnalogRead(uint8_t pin) {
    return analogRead(pin);
}