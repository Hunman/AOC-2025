#include "day3/joltage_meter.hpp"

#include <algorithm>

namespace {
    uint8_t digitToNumber(char d) {
        return static_cast<uint8_t>(d - '0');
    }

    template <uint64_t S>
    uint64_t maxDigit(const std::string &bank) {
        uint64_t result = 0;

        auto it = bank.begin();
        for (size_t i = 0; i < S; i++) {
            auto start = it;
            auto end = bank.end() - (S - i) + 1;

            it = std::max_element(start, end);

            result *= 10;
            result += digitToNumber(*it);

            it++;
        }

        return result;
    }
}

uint64_t JoltageMeter::maxDoubleDigit(const std::string &bank) {
    return maxDigit<2>(bank);
}

uint64_t JoltageMeter::maxTwelveDigit(const std::string &bank) {
    return maxDigit<12>(bank);
}
