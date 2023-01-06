#include "SerialInterface.h"

SerialInterface::SerialInterface()
{
}

/// @brief Attaches a stream to read packets from (probably Serial in
/// production, but a mock for testing)
/// @param io
void SerialInterface::attach(Stream* io)
{
    stream = io;
    return;
}

InformationPacket SerialInterface::decodePacket(char * rawPacket)
{
    InformationPacket packet;

    char *ptr;
    ptr = strtok(rawPacket, ";");
    packet.status = (int)atoi(ptr);
    ptr = strtok(NULL, ";");
    packet.x = (float)atoi(ptr) / 1023.0;
    ptr = strtok(NULL, ";");
    packet.y = (float)atoi(ptr) / 1023.0;
    return packet;
}

/// @brief Reads a packet from the stream
/// @return Returns latest packet
InformationPacket SerialInterface::readPacket()
{
    InformationPacket packet = this->latestPacket;
    char inputBuffer[PACKET_SIZE];
    if (stream->available() > 0)
    {
        if (stream->readBytesUntil('\0', inputBuffer, PACKET_SIZE) == PACKET_SIZE)
        {
            packet = decodePacket(inputBuffer);
            packet.timestamp = millis();
            this->latestPacket = packet;
        }
        // Clear buffer to avoid clogging
        while(stream->available() > 0)
        {
            char c = stream->read();
        }
    }
    return packet;
}