#pragma once
#include <cstdint>
#include <string>

class JoltageMeter {
public:
    static uint64_t maxDoubleDigit(const std::string &bank);
    static uint64_t maxTwelveDigit(const std::string &bank);

protected:
    JoltageMeter() = default;
};
