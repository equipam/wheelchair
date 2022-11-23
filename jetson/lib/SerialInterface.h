#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <libserial/SerialPort.h>

using LibSerial::SerialPort;

#define PACKET_SIZE 3

class SerialInterface
{
private:
    SerialPort serialStream;
public:
    SerialInterface();
    void setup(char* port);
    void cleanup();
    std::string createPacket(bool overwrite, int x, int y);
    void sendPacket(bool overwrite, int x, int y);
};

#endif
