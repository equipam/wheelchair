#if !defined(ARDUINO_H)
#define ARDUINO_H

#include "string.h"
#include <stdlib.h>
#include "ArduinoUnitMock.h"


#define INPUT 0
#define OUTPUT 0
#define INPUT_PULLUP 0
#define HIGH 1
#define LOW 0

int analogRead(int pin);
void analogWrite(int pin, int val);
int digitalRead(int pin);
void digitalWrite(int pin, int val);
void pinMode(int x, int mode);

#endif // ARDUINO
