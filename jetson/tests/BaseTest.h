#if !defined(BASETEST_H)
#define BASETEST_H

#define ASSERT(cond) (cond ? throw 1 : NULL)

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
