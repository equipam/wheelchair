#if !defined(TESTS_H)
#define TESTS_H

#include "BaseTest.h"
#include <vector>
#include <memory>
#include <cstring>

namespace Tests
{
    std::vector<std::shared_ptr<BaseTest>> getTests();
} // namespace Tests

#endif // TESTS_H
