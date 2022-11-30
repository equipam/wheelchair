// Production code

#include "Coordinates.h"
#include "Joystick.h"
#include "Chair.h"
#include "PinInterface.h"
#include "SerialInterface.h"
#include "Logging.h"

#define JOYSTICK_X_PIN A1
#define JOYSTICK_Y_PIN A2
#define INTERRUPT_PIN 2
#define INTERRUPT_READ_PIN 3
#define CHAIR_V_PIN 5
#define CHAIR_OMEGA_PIN 6

// Uncomment line below to enable logging
// #define LOGGING

RealPinInterface pinInterface;
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

  // Calibration process
  // joystick.calibrate(Serial);

  return;
}

void loop()
{
  joystickPosition = joystick.position();

  incomingPacket = serialInterface.readPacket();

  if (incomingPacket.overwrite)
  {
    joystickPosition.x = incomingPacket.x;
    joystickPosition.y = incomingPacket.y;
  }

  joystickPosition.x *= -0.8;
  joystickPosition.y *= -0.8;

  chair.command(joystickPosition);
}