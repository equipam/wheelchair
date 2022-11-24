#include "Tests.h"
#include "BaseTest.h"
#include "../lib/SerialInterface.h"

class SerialInterfaceTest : public BaseTest
{
public:
    void _run()
    {
        this->name = "Test SerialInterface";

        SerialInterface serialInterface;
        bool halt = 0;
        int x = 42;
        int y = 69;
        std::string expectedPacket = "0;0042;0069";
        std::string packet;
        packet = serialInterface.createPacket(halt, x, y);

        ASSERT(packet.compare(expectedPacket) == 0);
    }
};

namespace Tests
{
    std::vector<std::shared_ptr<BaseTest>> getTests()
    {
        std::vector<std::shared_ptr<BaseTest>> tests;
        tests.push_back(std::make_shared<SerialInterfaceTest>());
        return tests;
    }
} // namespace Tests
