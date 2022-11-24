#include "SerialInterface.h"


SerialInterface::SerialInterface()
{   
    #include <unistd.h>
    #include <cstdlib>
    #include <string>

    #include <iostream>

    using LibSerial::SerialPort ;
    SerialPort serial_port ;

    //char send = '\n';
    
    serial_port.Write("ROS\n");

    std::string input_buffer ;

    serial_port.ReadLine( input_buffer , '\n' ,5000) ;

    std::cout << input_buffer << std::endl ;
/*
    const int BUFFER_SIZE = 3;
    char output_buffer[BUFFER_SIZE];

    for( int i=0; i<BUFFER_SIZE; ++i )
    {
        output_buffer[i] = i;
    }

    serial_port.Write( output_buffer );
*/
    serial_port.Close() ;
}

void setup(char* port)
{
    LibSerial::SerialPort serial_port ;
    serial_port.Open(port) ;

    serial_port.SetBaudRate( LibSerial::BaudRate::BAUD_115200 ) ;
    serial_port.SetCharacterSize( LibSerial::CharacterSize::CHAR_SIZE_8 );
    serial_port.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    serial_port.SetParity(LibSerial::Parity::PARITY_NONE);
    serial_port.SetStopBits(LibSerial::StopBits::STOP_BITS_1);

    this->serialPort = serial_port;
}


/// @brief Takes 
/// @param halt 
/// @param x 
/// @param y 
/// @return 
char* packetCreator(bool overwrite, float x, float y)
{
    char packet[PACKET_SIZE];

    // ...

    return packet;
}


void cleanup()
{
    this->serialPort.Close()
}


void sendPacket(bool overwrite, float x, float y)
{
    // TODO
}