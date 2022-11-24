#if !defined(BASETEST_H)
#define BASETEST_H

#define ASSERT(cond) (cond ? NULL : throw 1)

#include <string>
#include <iostream>

class BaseTest
{
public:
    std::string name = "BaseTest";
    BaseTest();
    ~BaseTest();
    bool run();
    virtual void _run();
};

#endif // TEST_H
