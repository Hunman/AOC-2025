#include "day2/invalid_finder.hpp"

#include <cmath>
#include <sstream>
#include <type_traits>

namespace {
    template <typename... Ts>
    concept AreUnsignedIntegrals = ((std::is_integral_v<Ts> && std::is_unsigned_v<Ts>) && ...);

    template <typename B, typename E>
    requires AreUnsignedIntegrals<B, E>
    constexpr auto myPow(B base, E exponent) {
        if (exponent == 0) {
            return 1u;
        }

        return base * myPow(base, exponent - 1);
    }
} // namespace

bool InvalidFinder::checkTwice(uint64_t number) {
    auto length = static_cast<uint32_t>(log10(number)) + 1u;

    if (length % 2) {
        return false;
    }

    auto oneZerosOne = myPow(10u, length / 2u) + 1u;

    return number % oneZerosOne == 0;
}

bool InvalidFinder::checkAtLeastTwice(uint64_t number) {
    auto length = static_cast<uint32_t>(log10(number)) + 1u;

    for (uint32_t i = 1; i < length; i++) {
        uint32_t binary = 0;
        if (length % i != 0) {
            continue;
        }
        auto pattern = myPow(10u, i - 1u);

        std::stringstream ss;
        for (uint32_t j = 0; j < (length / i); j++) {
            ss << pattern;
        }
        {
            std::string str = ss.str();
            std::reverse(str.begin(), str.end());
            ss.str(std::string{});
            ss << str;
        }
        ss >> binary;

        if (number % binary == 0) {
            return true;
        }
    }

    return false;
}
