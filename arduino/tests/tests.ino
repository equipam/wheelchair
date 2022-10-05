// Write tests here (Must still upload to an Arduino to test)

#line 2 "tests.ino"
#include <ArduinoUnit.h>
#include <Stream.h>
#include "Coordinates.h"
#include "PinInterface.h"
#include "Joystick.h"
#include "Interrupt.h"
#include "Chair.h"

#define FAKE_PIN_AMMONT 5

float pins[FAKE_PIN_AMMONT] = {0};

void clearPins()
{
  for (size_t i = 0; i < FAKE_PIN_AMMONT; i++)
    pins[i] = 0.0;
}

class MockPinInterface : public PinInterface
{
public:
  void doDigitalWrite(uint8_t pin, uint8_t val)
  {
    pins[pin] = static_cast<float>(val);
  }
  int doDigitalRead(uint8_t pin)
  {
    return static_cast<int>(pins[pin]);
  }
  void doAnalogWrite(uint8_t pin, float val)
  {
    pins[pin] = val;
  }
  float doAnalogRead(uint8_t pin)
  {
    return pins[pin];
  }
};

test(joystick_calibration)
{
  clearPins();

  uint8_t xPin = 0;
  uint8_t yPin = 1;

  MockStream ms;              // fake serial port
  MockPinInterface interface; // fake pin interface
  Joystick joystick = Joystick(xPin, yPin, &interface);

  // User places joystick in each position and presses return key
  interface.doAnalogWrite(xPin, 1.5);
  interface.doAnalogWrite(yPin, 1.5);
  joystick.calibrate_middle(ms);

  interface.doAnalogWrite(xPin, 0.1);
  interface.doAnalogWrite(yPin, 1.5);
  joystick.calibrate_left(ms);

  interface.doAnalogWrite(xPin, 3);
  interface.doAnalogWrite(yPin, 1.5);
  joystick.calibrate_right(ms);

  interface.doAnalogWrite(xPin, 1.5);
  interface.doAnalogWrite(yPin, 3);
  joystick.calibrate_front(ms);

  interface.doAnalogWrite(xPin, 1.5);
  interface.doAnalogWrite(yPin, 0.1);
  joystick.calibrate_back(ms);

  // The real bound must be saved after calibration
  assertEqual(joystick.realBounds.minX, 0.1);
  assertEqual(joystick.realBounds.maxX, 3.0);
  assertEqual(joystick.realBounds.minY, 0.1);
  assertEqual(joystick.realBounds.maxY, 3.0);
}

test(joystick_position)
{
  // Assuming our scale is [0, 1] in both x and y axis
  clearPins();
  uint8_t xPin = 0;
  uint8_t yPin = 1;

  MockPinInterface interface; // fake pin interface
  Joystick joystick = Joystick(xPin, yPin, &interface);
  joystick.realBounds.minX = 0.0;
  joystick.realBounds.maxX = 3.0;
  joystick.realBounds.minY = 0.0;
  joystick.realBounds.maxY = 3.0;
  // Joystick is halfway in both axis
  float expectedX = (STANDARDIZED_X_MAX + STANDARDIZED_X_MIN) / 2;
  float expectedY = (STANDARDIZED_Y_MAX + STANDARDIZED_Y_MIN) / 2;
  interface.doAnalogWrite(xPin, 1.5);
  interface.doAnalogWrite(yPin, 1.5);

  LinearCoords position = joystick.position();

  assertEqual(position.x, expectedX);
  assertEqual(position.y, expectedY);
}

test(joystick_mapping)
{
  // Assuming our scale is [0, 1] in both x and y axis
  MockPinInterface interface; // fake pin interface
  Joystick joystick = Joystick(0, 1, &interface);
  joystick.realBounds.minX = 0.0;
  joystick.realBounds.maxX = 3.0;
  joystick.realBounds.minY = 0.0;
  joystick.realBounds.maxY = 3.0;

  float expectedX = (STANDARDIZED_X_MAX + STANDARDIZED_X_MIN) / 2;
  float expectedY = (STANDARDIZED_Y_MAX + STANDARDIZED_Y_MIN) / 2;
  LinearCoords realPosition = {.x = 1.5, .y = 1.5};
  LinearCoords standardizedPosition = joystick.joystickMapping(realPosition);

  assertEqual(standardizedPosition.x, expectedX);
  assertEqual(standardizedPosition.y, expectedY);
}

test(interrupt)
{
  clearPins();
  int interruptPin = 0;
  bool mustStop;
  MockPinInterface interface;
  Interrupt interrupt = Interrupt(interruptPin, &interface);

  // interrupt pin is high, must stop
  interface.doDigitalWrite(interruptPin, HIGH);
  mustStop = interrupt.mustStop();
  assertEqual(mustStop, true);

  // interrupt pin is low, must stop
  interface.doDigitalWrite(interruptPin, LOW);
  mustStop = interrupt.mustStop();
  assertEqual(mustStop, false);
}

test(chair)
{
  clearPins();
  uint8_t vPin = 0;
  uint8_t omegaPin = 1;
  MockPinInterface interface;

  Chair chair = Chair(vPin, omegaPin, &interface);
  // command the max speed at max angle
  PolarCoords command = {.v = STANDARDIZED_V_MAX, .omega = STANDARDIZED_OMEGA_MAX};

  chair.command(command);

  // should be max voltage on both v and omega pins (3.3)
  assertEqual(pins[0], 3.3);
  assertEqual(pins[1], 3.3);
}

test(coordinates)
{
  LinearCoords xy = {.x = -1, .y = 0};
  PolarCoords vo = Coordinates::linearToPolar(xy);
  assertEqual(vo.v, 1);
  assertEqual(vo.omega, 90); // omega between -180 and 180 degrees ?
}

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  } // Portability for Leonardo/Micro
}

void loop()
{
  Test::run();
}