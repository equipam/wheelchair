#ifndef PACKETS_H
#define PACKETS_H

#include <Arduino.h>

#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>


namespace Packets {
    struct InformationPacket
    {
        bool overwrite;
        float x;
        float y;
    };

    InformationPacket decode(String rawInput);
}

#endif