#include "SerialInterface.h"
#include <libserial/SerialPort.h>
//#include <libserial/SerialStream.h>

#include <cstddef>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <cstring>

#include <iostream>

//using namespace LibSerial; 
using LibSerial::SerialPort;

SerialInterface::SerialInterface()
{
    SerialPort serial_stream;
}

/// @brief Connects interface to serial port
/// @param port The port name to connect to (e.g. "/dev/ttyUSB0")
void SerialInterface::setup(char* port)
{
    try
        {
            serial_stream.Open(&port);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    // Set the baud rates.
    using LibSerial::BaudRate ;
    serial_stream.SetBaudRate( BaudRate::BAUD_115200 ) ;
    serial_stream.SetCharacterSize( LibSerial::CharacterSize::CHAR_SIZE_8);
    serial_stream.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    serial_stream.SetParity(LibSerial::Parity::PARITY_NONE);
    serial_stream.SetStopBits(LibSerial::StopBits::STOP_BITS_1);

    return;
}

/// @brief Disconnects from the current serial port
void SerialInterface::cleanup()
{
    serial_stream.Close();
    return;
}

/// @brief Creates a fixed length char information packet to relay
/// Example: halt=1, x=1023 and y=1023 returns "1;1023;1023"
/// @param halt 
/// @param x 
/// @param y 
/// @return Returns a fixed length char array of the packet
char SerialInterface::createPacket(bool halt, float x, float y)
{
    //char send[12] = "1;0001;0069";
    char send[11] = "";
    send[0] = '0' + halt;
    send[1] = ';';
    send[2] = '0' + (int)x / 1000 % 10;
    send[3] = '0' + (int)x / 100 % 10;
    send[4] = '0' + (int)x / 10 % 10;
    send[5] = '0' + (int)x / 1 % 10;
    send[6] = ';';
    send[7] = '0' + (int)y / 1000 % 10;
    send[8] = '0' + (int)y / 100 % 10;
    send[9] = '0' + (int)y / 10 % 10;
    send[10] = '0' + (int)y / 1 % 10;

    return send;
}

/// @brief Creates and sends a packet to the serial port
/// @param halt 
/// @param x 
/// @param y 
void SerialInterface::sendPacket(bool halt, float x, float y)
{
    //std::string input_buffer;
    char send[11] = createPacket(halt, x, y)
    //std::cout << send << std::endl;

    try
    {
        serial_stream.Write(send);
        //serial_stream.ReadLine(input_buffer);
        //std::cout << input_buffer << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return;
}
