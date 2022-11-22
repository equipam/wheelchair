#include "SerialInterface.h"

SerialInterface::SerialInterface()
{
}

/// @brief Attaches a stream to read packets from (probably Serial in
/// production, but a mock for testing)
/// @param io 
void attach(Stream &io)
{
    // TODO
    return;
}

/// @brief Reads a packet from the stream
/// @return Returns latest packet
InformationPacket readPacket()
{
    InformationPacket packet;
    // TODO
    return packet;
}