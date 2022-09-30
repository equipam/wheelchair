// Write unit tests here (Must still upload to an Arduino to test)
//TODO #6 Write arduino acceptace tests

#line 2 "tests.ino"
#include <ArduinoUnit.h>
//TODO Figure out if there is any way of importing .h files from other folder
#include "Coordinates.h"

test(coordinates)
{
  LinearCoords xy = {.x = 0, .y = 0};
  PolarCoords vo = Coordinates::linearToPolar(xy);
  assertEqual(vo.v, 1);
  assertEqual(vo.omega, 1);
}

void setup()
{
  Serial.begin(9600);
  while(!Serial) {} // Portability for Leonardo/Micro
}

void loop()
{
  Test::run();
}