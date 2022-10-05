// Production code

#include "Coordinates.h"
#include "Interrupt.h"
#include "Joystick.h"
#include "Chair.h"
#include "PinInterface.h"

#define JOYSTICK_X_PIN 19
#define JOYSTICK_Y_PIN 20
#define INTERRUPT_PIN 5
#define CHAIR_V_PIN 21
#define CHAIR_OMEGA_PIN 22

RealPinInterface pinInterface;
Joystick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, &pinInterface);
Interrupt haltInterrupt(INTERRUPT_PIN);
Interrupt continueInterrupt(INTERRUPT_PIN);
Chair chair(CHAIR_V_PIN, CHAIR_OMEGA_PIN, &pinInterface);

LinearCoords joystickPosition;
PolarCoords chairCoordsCommand;

void stop(){
    chair.setHalt(true);
}

void proceed(){
    chair.setHalt(false);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Pin Setup
    joystick.setup();
    chair.setup();

    // Calibration process
    Serial.write("Place the joystick forward. Press any key");
    Serial.read();
    joystick.calibrate_front(Serial);
    Serial.write("Place the joystick back. Press any key");
    Serial.read();
    joystick.calibrate_back(Serial);
    Serial.write("Place the joystick left. Press any key");
    Serial.read();
    joystick.calibrate_left(Serial);
    Serial.write("Place the joystick right. Press any key");
    Serial.read();
    joystick.calibrate_right(Serial);

    // Interrupt Setup
    haltInterrupt.setup(stop, RISING);
    continueInterrupt.setup(proceed, FALLING);

    return;
}

void loop()
{
    joystickPosition = joystick.position();
    chairCoordsCommand = Coordinates::linearToPolar(joystickPosition);
    chair.command(chairCoordsCommand);
}
