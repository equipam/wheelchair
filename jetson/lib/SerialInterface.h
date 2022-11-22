#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include <libserial/SerialPort.h>
class SerialInterface
{
private:
    LibSerial::SerialPort serialStream;
public:
    SerialInterface();
    void setup(char* port);
    void cleanup();
    std::string createPacket(bool halt, int x, int y);
    void sendPacket(bool halt, int x, int y);
};

#endif
