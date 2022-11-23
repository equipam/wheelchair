#include "Packets.h"

using namespace std;
using namespace Packets;

InformationPacket decode(String rawInput) //CHECK - Only test version
{
    bool a=false;
    int b=0;
    int c=0;
    string text{"1;0069;0052"};

    char const* psz_delimiter{";"};

    char* psz_token{::std::strtok(text.data(), psz_delimiter)};

    ::std::cout << psz_token << ::std::endl;
    a =stoi(psz_token);
    cout << "Check 1 - " << (!!a) << endl;
    psz_token = std::strtok(nullptr, psz_delimiter);
    

    ::std::cout << psz_token << ::std::endl;
    b =stoi(psz_token);
    cout << "Check 2 - " << b+2 << endl;
    psz_token = std::strtok(nullptr, psz_delimiter);
    


    ::std::cout << psz_token << ::std::endl;
    c =stoi(psz_token);
    cout << "Check 3 - " << c << endl;

    return 1;


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