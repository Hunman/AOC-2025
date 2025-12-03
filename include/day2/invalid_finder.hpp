#pragma once
#include <cstdint>

class InvalidFinder {
public:
    static bool checkTwice(uint64_t number);
    static bool checkAtLeastTwice(uint64_t number);

protected:
    InvalidFinder() = default;
};
