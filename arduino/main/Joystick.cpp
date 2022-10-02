//TODO #3 Identify axis boundaries (XY) on the joystick setup and map them to known scales

#include "Joystick.h"

Joystick::Joystick(int xPin, int yPin, PinInterface* pinInterface){
    this->xPin = xPin;
    this->yPin = yPin;
    this->pinInterface = pinInterface;
    return;
}

void Joystick::calibrate(Stream &io){
    //TODO #10 Create joystick calibration function
    // ask the user to place the joystick in forward, back, left and write positions,
    // storing the real bounds on the class attribute "realBounds"
}

void Joystick::calibrate_left(Stream &io){
    return;
}
void Joystick::calibrate_right(Stream &io){
    return;
}
void Joystick::calibrate_front(Stream &io){
    return;
}
void Joystick::calibrate_back(Stream &io){
    return;
}

LinearCoords Joystick::joystickMapping(LinearCoords realCoords){
    // vx and vy are real values from the joystick
    // returns normalized values of x and y on a tuple
    LinearCoords normalizedCoords = {.x = 0.0, .y = 0.0};
    normalizedCoords.x = realCoords.x / abs(realBounds.maxX-realBounds.minX);
    normalizedCoords.y = realCoords.y / abs(realBounds.maxY-realBounds.minY); 
    return normalizedCoords;
}

LinearCoords Joystick::position(){
    // magic ...
    //TODO #11 Create function that returns joystick normalized position
    LinearCoords pos = {.x = 0.0, .y = 0.0};
    //get pos from joystick and normalize it
    pos = joystickMapping(pos);
    return pos;
}
