#include "Packets.h"

using namespace Packets;

InformationPacket decode(String rawInput)
{
    // TODO
}


/*PacketHandler::PacketHandler()
{

}

void SerialInterface::readPacket()
{
    using LibSerial::SerialStream ;

    SerialStream serial_stream ;
    serial_stream.Open( "/dev/ttyUSB0" ) ;

    // Set the baud rates.
    using LibSerial::BaudRate ;
    serial_stream.SetBaudRate( BaudRate::BAUD_115200 ) ;

    size_t timeout_milliseconds = 500 ;

    const int BUFFER_SIZE = 3 ;
    char input_buffer[BUFFER_SIZE] ;

    using LibSerial::ReadTimeout ;
    try
    {
    serial_stream.read( input_buffer, BUFFER_SIZE ) ;
    }
    catch (const ReadTimeout&)
    {
        std::cerr << "The Read() call has timed out." << std::endl ;
    }

    std::cout << input_buffer << std::endl ;

    serial_stream.Close() ;
}*/