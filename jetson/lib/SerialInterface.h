#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <libserial/SerialPort.h>

using LibSerial::SerialPort;

#define PACKET_SIZE 3

class SerialInterface
{
private:
    SerialPort serial_port;
    void packetCreator(bool overwrite, float x, float y);
public:
    SerialInterface();
    void setup(char* port);
    void cleanup();
    void sendPacket(bool overwrite, float x, float y);
};

#endif
