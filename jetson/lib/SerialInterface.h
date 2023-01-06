#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <libserial/SerialPort.h>

using LibSerial::SerialPort;

#define PACKET_SIZE 3

class SerialInterface
{
public:
    SerialPort serialStream;
    SerialInterface();
    void setup(char *port);
    void cleanup();
    std::string createPacket(int status, int x, int y);
    void sendPacket(int status, int x, int y);
};

#endif
