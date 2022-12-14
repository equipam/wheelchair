//
// The regular arduino build should ignore this file,
// it is only to mock the arduino environment when
// compiled "en vitro" on the dev system.
//
#if !defined(ARDUINO)

#include "ArduinoUnit.h"
#include "ArduinoUnitMock.h"

void setup();
void loop();

// CppIOStream wraps stdin/stdout as a mock Serial device
CppIOStream Serial;

// you will have to mock any other parts you use, perhaps
// with a more complete mocking library...
int analogRead(int pin){return 1;}
void analogWrite(int pin, int val){}
int digitalRead(int pin){return 1;}
void digitalWrite(int pin, int val){}
void pinMode(int x, int mode){}

int main(int argc, const char *argv[]) {
  int timeLimitMicros = 10000;

  setup();

  // loop until tests complete 
  while (Test::remaining() > 0 && micros() < timeLimitMicros) {
    loop();
  }

  // abort (fail) any remaining tests
  Test::abort();

  if (Test::getCurrentFailed() == 0) {
    return 0;
  } else {
    return 1;
  }
}

// include the "ino" here...
#include "tests.ino"

#endif
