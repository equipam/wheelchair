#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H


class SerialInterface
{
public:
    SerialInterface();
    void setup(char* port);
    void cleanup();
    char* createPacket(bool halt, float x, float y);
    void sendPacket(bool halt, float x, float y);
};

#endif
