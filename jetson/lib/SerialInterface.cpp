#include "SerialInterface.h"

SerialInterface::SerialInterface()
{
}

/// @brief Connects interface to serial port
/// @param port The port name to connect to (e.g. "/dev/ttyUSB0")
void setup(char* port)
{
    // TODO
    return;
}

/// @brief Disconnects from the current serial port
void cleanup()
{
    // TODO
    return;
}

/// @brief Creates a fixed length char information packet to relay
/// Example: halt=1, x=1023 and y=1023 returns "1;1023;1023"
/// @param halt 
/// @param x 
/// @param y 
/// @return Returns a fixed length char array of the packet
char* createPacket(bool halt, float x, float y)
{
    // TODO
    return "";
}

/// @brief Creates and sends a packet to the serial port
/// @param halt 
/// @param x 
/// @param y 
void sendPacket(bool halt, float x, float y)
{
    // TODO
    return;
}