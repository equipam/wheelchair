#include "../lib/SerialInterface.h"
#include <iostream>
#include <time.h>
#include <unistd.h>

#include <libserial/SerialPort.h>
#include <libserial/SerialStream.h>

int main()
{
    SerialInterface serial;
    char * port = "/dev/ttyUSB0";
    serial.setup(port);
    int status = 0;
    int counter = 0;
    std::cout << status << std::endl;
    // Read a whole array of data from the serial port.
    const int BUFFER_SIZE = 256;
    std::string input_buffer;

    while (true)
    {
        std::cout << serial.createPacket(status, 0.0, 0.0) << std::endl;
        serial.sendPacket(status, 0.0, 0.0);
        // serial.serialStream.Read(input_buffer);
        // std::cout << input_buffer << std::endl;
        counter++;
        if(counter == 10)
        {
            counter = 0;
            status = (status + 1) % 3;
            std::cout << status << std::endl;
        }
        usleep(1000); // sleep for 100000 microseconds (0.01 seconds)
    }
    
    return 0;
}
