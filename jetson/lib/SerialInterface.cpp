#include "SerialInterface.h"

#include <libserial/SerialPort.h>
#include <cstddef>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>

// using namespace LibSerial;
using LibSerial::SerialPort;

SerialInterface::SerialInterface()
{
    SerialPort serialStream;
}

/// @brief Connects interface to serial port
/// @param port The port name to connect to (e.g. "/dev/ttyUSB0")
void SerialInterface::setup(char *port)
{
    try
    {
        serialStream.Open(port);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    // Set the baud rates.
    using LibSerial::BaudRate;
    serialStream.SetBaudRate(BaudRate::BAUD_115200);
    serialStream.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
    serialStream.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    serialStream.SetParity(LibSerial::Parity::PARITY_NONE);
    serialStream.SetStopBits(LibSerial::StopBits::STOP_BITS_1);
    return;
}

/// @brief Disconnects from the current serial port
void SerialInterface::cleanup()
{
    serialStream.Close();
    return;
}

/// @brief Creates a fixed length char information packet to relay
/// Example: status=1, x=1023 and y=1023 returns "1;1023;1023"
/// @param status
/// @param x
/// @param y
/// @return Returns a fixed length char array of the packet
std::string SerialInterface::createPacket(int status, int x, int y)
{
    // char send[12] = "1;0001;0069";
    char send[11] = {'\0'};
    send[0] = '0' + status;
    send[1] = ';';
    send[2] = '0' + x / 1000 % 10;
    send[3] = '0' + x / 100 % 10;
    send[4] = '0' + x / 10 % 10;
    send[5] = '0' + x / 1 % 10;
    send[6] = ';';
    send[7] = '0' + y / 1000 % 10;
    send[8] = '0' + y / 100 % 10;
    send[9] = '0' + y / 10 % 10;
    send[10] = '0' + y / 1 % 10;

    return std::string(send);
}

/// @brief Creates and sends a packet to the serial port
/// @param status
/// @param x
/// @param y
void SerialInterface::sendPacket(int status, int x, int y)
{
    std::string send = createPacket(status, x, y);

    try
    {
        serialStream.Write(send.c_str());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return;
}
