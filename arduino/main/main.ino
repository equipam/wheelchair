// Production code
//TODO #7 Create arduino main routine logic

#include "coordinates.h"
#include "interrupt.h"
#include "joystick.h"
#include "chair.h"

// TODO Decide pin layout
#define JOYSTICK_X_PIN 0
#define JOYSTICK_Y_PIN 1
#define INTERRUPT_PIN 2
#define CHAIR_V_PIN 3
#define CHAIR_OMEGA_PIN 4

Joystick joystick = Joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN);
Interrupt interrupt = Interrupt(INTERRUPT_PIN);
Chair chair = Chair(CHAIR_V_PIN, CHAIR_OMEGA_PIN);

LinearCoords joystickPosition;
PolarCoords chairCoordsCommand;

void setup(){
    // Pin setup
    pinMode(JOYSTICK_X_PIN, INPUT);
    pinMode(JOYSTICK_Y_PIN, INPUT);
    pinMode(INTERRUPT_PIN, INPUT);
    pinMode(CHAIR_V_PIN, OUTPUT);
    pinMode(CHAIR_OMEGA_PIN, OUTPUT);
    joystick.calibrate();
    return;
}

void loop(){
    joystickPosition = joystick.position();
    chairCoordsCommand = Coordinates::linearToPolar(joystickPosition);
    if(interrupt.mustStop()){
        joystickPosition = joystick.position();
        // Wait until user let go of the joystick
        while (joystickPosition.x != 0 && joystickPosition.y != 0)
        {
            delay(100);
            joystickPosition = joystick.position();
        }
    }
    chair.command(chairCoordsCommand);
}

