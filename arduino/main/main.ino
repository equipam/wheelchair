// Production code

#include "Coordinates.h"
#include "Interrupt.h"
#include "Joystick.h"
#include "Chair.h"
#include "PinInterface.h"

#define JOYSTICK_X_PIN 19
#define JOYSTICK_Y_PIN 20
#define INTERRUPT_PIN 2
#define INTERRUPT_READ_PIN 3
#define CHAIR_V_PIN 21
#define CHAIR_OMEGA_PIN 22

RealPinInterface pinInterface;
Joystick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, &pinInterface);
Interrupt haltInterrupt(INTERRUPT_PIN);
Chair chair(CHAIR_V_PIN, CHAIR_OMEGA_PIN, &pinInterface);

LinearCoords joystickPosition;
PolarCoords chairCoordsCommand;

void interruptFcn(){
    chair.setHalt(pinInterface.doDigitalRead(INTERRUPT_READ_PIN));
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
    Serial.write("Don't touch the joystick. Press any key");
    while(Serial.read()==-1){}
    joystick.calibrate_middle();
    Serial.write("Place the joystick forward. Press any key");
    while(Serial.read()==-1){}
    joystick.calibrate_front();
    Serial.write("Place the joystick back. Press any key");
    while(Serial.read()==-1){}
    joystick.calibrate_back();
    Serial.write("Place the joystick left. Press any key");
    while(Serial.read()==-1){}
    joystick.calibrate_left();
    Serial.write("Place the joystick right. Press any key");
    while(Serial.read()==-1){}
    joystick.calibrate_right();

    // Interrupt Setup
    pinMode(INTERRUPT_READ_PIN, INPUT);
    haltInterrupt.setup(interruptFcn, CHANGE);

    return;
}

void loop()
{
    joystickPosition = joystick.position();
    //chairCoordsCommand = Coordinates::linearToPolar(joystickPosition);
    chair.command(joystickPosition);
}
