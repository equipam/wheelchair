#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include "Arduino.h"

#define PACKET_SIZE 11

struct InformationPacket
{
    int status;
    float x;
    float y;
    unsigned long timestamp;
};

class SerialInterface
{
private:
    Stream* stream;
    InformationPacket latestPacket = {.status = -1, .x = 0.0, .y = 0.0, .timestamp = 0};
public:
    SerialInterface();
    void attach(Stream* io);
    InformationPacket decodePacket(char* rawPacket);
    InformationPacket readPacket();
};

#endif
