// Production code

#include "Coordinates.h"
#include "Interrupt.h"
#include "Joystick.h"
#include "Chair.h"
#include "PinInterface.h"
#include "Filter.h"

#define JOYSTICK_X_PIN A1
#define JOYSTICK_Y_PIN A2
#define INTERRUPT_PIN 2
#define INTERRUPT_READ_PIN 3
#define CHAIR_V_PIN A3
#define CHAIR_OMEGA_PIN A4

#if false
  #define sp(...) Serial.print(__VA_ARGS__);
  #define spl(...) Serial.println(__VA_ARGS__);
#else
  #define sp(...)
  #define spl(...)
#endif

RealPinInterface pinInterface;
Joystick joystick(JOYSTICK_X_PIN, JOYSTICK_Y_PIN, &pinInterface);
Filter filter;
Interrupt haltInterrupt(INTERRUPT_PIN);
Chair chair(CHAIR_V_PIN, CHAIR_OMEGA_PIN, &pinInterface);

LinearCoords joystickPosition;

void interruptFcn(){
    chair.setHalt(pinInterface.doDigitalRead(INTERRUPT_READ_PIN));
}

void calibrate()
{
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
    calibrate();

    // Interrupt Setup
    pinMode(INTERRUPT_READ_PIN, INPUT);
    haltInterrupt.setup(interruptFcn, CHANGE);

    return;
}

void loop()
{
    joystickPosition = joystick.position();
    
    joystickPosition = filter.apply(joystickPosition);

    sp("x = ");
    sp(joystickPosition.x);
    sp(" | y = ");
    spl(joystickPosition.y);
    chair.command(joystickPosition);
}
