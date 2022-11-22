#include "../lib/SerialInterface.h"
#include "Tests.h"
#include "BaseTest.h"
#include <cstring>
#include <cassert>
#include <memory>
#include <vector>

int main(){
	std::vector<std::shared_ptr<BaseTest>> tests;
    tests = Tests::getTests();
    bool failing = false;
    for (size_t i = 0; i < tests.size(); i++)
    {
        if (!tests[i]->run())
        {
            failing = true;
        }
    }

    if (failing)
    {
        return -1;
    }

	return 0;
}
