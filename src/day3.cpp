#include <filesystem>
#include <fstream>
#include <iostream>

#include "stopwatch.hpp"
#include "day3/joltage_meter.hpp"

namespace {
    std::vector<std::string> getLines() {
        std::ifstream in{std::filesystem::path(INPUT_DIRECTORY) / "day3.txt"};

        auto lineCount = 0uz;
        for (std::string line; std::getline(in, line);) {
            lineCount++;
        }

        std::vector<std::string> lines{lineCount};
        in.clear();
        in.seekg(0);

        for (size_t i = 0uz; i < lineCount; i++) {
            std::getline(in, lines[i]);
        }

        return lines;
    }

    size_t exercise1(const std::vector<std::string> &lines) {
        auto sum = 0uz;

        for (const auto &line: lines) {
            sum += JoltageMeter::maxDoubleDigit(line);
        }

        return sum;
    }

    size_t exercise2(const std::vector<std::string> &lines) {
        auto sum = 0uz;

        for (const auto &line: lines) {
            sum += JoltageMeter::maxTwelveDigit(line);
        }

        return sum;
    }
}

int main() {
    std::printf("[Parsing inputs]\n");
    auto lines = stopwatch("   ", [] {
        return getLines();
    });

    std::printf("\n[Exercise 1]\n");
    auto e1 = stopwatch("   ", [&lines] {
        return exercise1(lines);
    });
    std::printf("    the result is %lu\n", e1);

    std::printf("\n[Exercise 2]\n");
    auto e2 = stopwatch("   ", [&lines] {
        return exercise2(lines);
    });
    std::printf("    the result is %lu\n", e2);

    return 0;
}
