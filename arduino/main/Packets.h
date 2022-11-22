#ifndef PACKETS_H
#define PACKETS_H

#include <Arduino.h>

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