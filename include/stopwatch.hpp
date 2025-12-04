#pragma once

#include <chrono>
#include <iostream>

class Watch {
public:
    Watch(): start(std::chrono::high_resolution_clock::now()) {
        // Empty
    }

    ~Watch() {
        using std::chrono_literals::operator""ms, std::chrono_literals::operator""s;
        auto diff = std::chrono::high_resolution_clock::now() - start;

        std::cout << "    Ran for: " << std::chrono::duration_cast<std::chrono::microseconds>(diff) << " ≈ "
                  << diff / 1ms << "ms ≈ " // almost equivalent form of the above, but
                  << diff / 1s << "s.\n"; // using milliseconds and seconds accordingly
    }

private:
    const std::chrono::high_resolution_clock::time_point start;
};
