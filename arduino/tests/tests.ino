// Write tests here (Must still upload to an Arduino to test)

#line 2 "tests.ino"
#include <ArduinoUnit.h>
#include "Coordinates.h"
#include "PinInterface.h"
#include "Joystick.h"
#include "Chair.h"
#include "SerialInterface.h"

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

  MockPinInterface interface; // fake pin interface
  Joystick joystick = Joystick(xPin, yPin, &interface);

  // User places joystick in each position and presses return key
  interface.doAnalogWrite(xPin, 1.5);
  interface.doAnalogWrite(yPin, 1.5);
  joystick.calibrate_middle();

  interface.doAnalogWrite(xPin, 0.1);
  interface.doAnalogWrite(yPin, 1.5);
  joystick.calibrate_left();

  interface.doAnalogWrite(xPin, 3);
  interface.doAnalogWrite(yPin, 1.5);
  joystick.calibrate_right();

  interface.doAnalogWrite(xPin, 1.5);
  interface.doAnalogWrite(yPin, 3);
  joystick.calibrate_front();

  interface.doAnalogWrite(xPin, 1.5);
  interface.doAnalogWrite(yPin, 0.1);
  joystick.calibrate_back();

  // The real bound must be saved after calibration
  // Use difference to account for float imprecision...
  assertLess(abs(joystick.realBounds.minX - 0.1), 0.00001);
  assertLess(abs(joystick.realBounds.maxX - 3.0), 0.00001);
  assertLess(abs(joystick.realBounds.minY - 0.1), 0.00001);
  assertLess(abs(joystick.realBounds.maxY - 3.0), 0.00001);
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

test(chair)
{
  clearPins();
  uint8_t vPin = 0;
  uint8_t omegaPin = 1;
  MockPinInterface interface;

  Chair chair = Chair(vPin, omegaPin, &interface);
  // command the max speed at max angle
  LinearCoords command = {.x = STANDARDIZED_V_MAX, .y = STANDARDIZED_OMEGA_MAX};

  chair.command(command);

  // should be max voltage on both v and omega pins (3.3)
  assertLess(abs(pins[0] - 3.3), 0.00001);
  assertLess(abs(pins[1] - 3.3), 0.00001);
}

test(serial_interface)
{
  MockStream ms;
  SerialInterface serialInterface = SerialInterface();

  serialInterface.attach(&ms);

  ms.input.print("0;0042;0069");
  InformationPacket expectedPacket = {.overwrite=false, .x=42.0/1023.0, .y=69.0/1023.0};

  InformationPacket result;
  result = serialInterface.readPacket();
  
  assertEqual(result.overwrite, expectedPacket.overwrite);
  assertEqual(result.x, expectedPacket.x);
  assertEqual(result.y, expectedPacket.y);
}

test(decode)
{
  SerialInterface serialInterface = SerialInterface();

  InformationPacket expectedPacket = {.overwrite=false, .x=42.0/1023.0, .y=69.0/1023.0};

  char rawPacket[12] = "0;0042;0069";

  InformationPacket result;
  result = serialInterface.decodePacket(rawPacket);
  
  assertEqual(result.overwrite, expectedPacket.overwrite);
  assertEqual(result.x, expectedPacket.x);
  assertEqual(result.y, expectedPacket.y);
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