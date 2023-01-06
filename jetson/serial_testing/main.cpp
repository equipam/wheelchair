#include "../lib/SerialInterface.h"
#include <iostream>
#include <time.h>

int main()
{
    SerialInterface serial;
    char * port = "/dev/ttyUSB0";
    serial.setup(port);
    int overwrite = 0;
    int counter = 0;
    std::cout << overwrite << std::endl;
    while (true)
    {
        serial.sendPacket(overwrite, 0.0, 0.0);
        counter++;
        if(counter == 1000)
        {
            counter = 0;
            overwrite = (overwrite + 1) % 3;
            std::cout << overwrite << std::endl;
        }
    }
    
    return 0;
}