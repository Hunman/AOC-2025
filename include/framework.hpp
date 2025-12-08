#pragma once
#include "watch.hpp"

#include <filesystem>

template <typename T>
class Framework {
public:
    static void run() {
        std::printf("[Day %zu]\n", T::DAY);

        printf("Reading input\n");
        auto input = ([]() {
            Watch watch;
            return T::getInput();
        })();

        printf("Exercise 1\n");
        auto r1 = ([](const auto &input) {
            Watch watch;
            return T::exercise1(input);
        })(input);
        std::cout << "    Result: " << r1 << "\n";

        printf("Exercise 2\n");
        auto r2 = ([](const auto &input) {
            Watch watch;
            return T::exercise2(input);
        })(input);
        std::cout << "    Result: " << r2 << "\n";
    }
};

template <size_t D>
class Day {
public:
    static constexpr auto DAY = D;

protected:
    static constexpr std::filesystem::path getInputPath() {
        using std::string_literals::operator""s;

        return std::filesystem::path(INPUT_FILE);
    }
};
