// Production code

#include "Coordinates.h"
#include "Interrupt.h"
#include "Joystick.h"
#include "Chair.h"
#include "PinInterface.h"

#define JOYSTICK_X_PIN 19
#define JOYSTICK_Y_PIN 20
#define INTERRUPT_PIN 10
#define CHAIR_V_PIN 21
#define CHAIR_OMEGA_PIN 22

RealPinInterface pinInterface;
Joystick joystick = Joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, &pinInterface);
Interrupt interrupt = Interrupt(INTERRUPT_PIN, &pinInterface);
Chair chair = Chair(CHAIR_V_PIN, CHAIR_OMEGA_PIN, &pinInterface);

LinearCoords joystickPosition;
PolarCoords chairCoordsCommand;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    // Pin setup
    pinMode(JOYSTICK_X_PIN, INPUT);
    pinMode(JOYSTICK_Y_PIN, INPUT);
    pinMode(INTERRUPT_PIN, INPUT);
    pinMode(CHAIR_V_PIN, OUTPUT);
    pinMode(CHAIR_OMEGA_PIN, OUTPUT);

    // Calibration process
    Serial.write("Place the joystick forward. Press return");
    joystick.calibrate_front(Serial);
    Serial.write("Place the joystick back. Press return");
    joystick.calibrate_back(Serial);
    Serial.write("Place the joystick left. Press return");
    joystick.calibrate_left(Serial);
    Serial.write("Place the joystick right. Press return");
    joystick.calibrate_right(Serial);

    return;
}

void loop()
{
    joystickPosition = joystick.position();
    chairCoordsCommand = Coordinates::linearToPolar(joystickPosition);
    if (interrupt.mustStop())
    {
        joystickPosition = joystick.position();
        // Wait until user let go of the joystick
        while (joystickPosition.x != 0 && joystickPosition.y != 0 && interrupt.mustStop())
        {
            delay(100);
            joystickPosition = joystick.position();
        }
    }
    chair.command(chairCoordsCommand);
}
