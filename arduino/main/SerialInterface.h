#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <Arduino.h>

struct InformationPacket
{
    bool halt;
    float x;
    float y;
};



class SerialInterface
{
private:
    InformationPacket latestPacket = {.halt = false, .x = 0.0, .y = 0.0};
public:
    SerialInterface();
    void attach(Stream &io);
    void readPacket();
};

#endif
