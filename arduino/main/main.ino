// Production code

#include "Coordinates.h"
#include "Joystick.h"
#include "Chair.h"
#include "PinInterface.h"
#include "RealPinInterface.h"
#include "SerialInterface.h"
#include "Logging.h"
#include "Led.h"

#define JOYSTICK_X_PIN A1
#define JOYSTICK_Y_PIN A2
#define INTERRUPT_PIN 2
#define INTERRUPT_READ_PIN 3
#define CHAIR_V_PIN 5
#define CHAIR_OMEGA_PIN 6
#define GREEN_LED_PIN 10
#define YELLOW_LED_PIN 11
#define RED_LED_PIN 12

// Uncomment line below to enable logging
// #define LOGGING
RealPinInterface pinInterface;
Led led(RED_LED_PIN, YELLOW_LED_PIN, GREEN_LED_PIN, &pinInterface);
Joystick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, &pinInterface);
Chair chair(CHAIR_V_PIN, CHAIR_OMEGA_PIN, &pinInterface);
SerialInterface serialInterface;

LinearCoords joystickPosition;
InformationPacket incomingPacket;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  }
  serialInterface.attach(Serial);

  // Pin Setup
  joystick.setup();
  chair.setup();
  led.setup()

  // Calibration process
  // joystick.calibrate(Serial);

  return;
}

void loop()
{
  joystickPosition = joystick.position();

  incomingPacket = serialInterface.readPacket();

  led.update(incomingPacket.overwrite);

  if (incomingPacket.overwrite == 2)
  {
    joystickPosition.x = incomingPacket.x;
    joystickPosition.y = incomingPacket.y;
  }

  joystickPosition.x *= -0.9;
  joystickPosition.y *= -0.9;

  chair.changeSpeed();
  chair.command(joystickPosition);
}