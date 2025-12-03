#include "day3/joltage_meter.hpp"
#include "stopwatch.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <ranges>

namespace {
    constexpr auto execution = std::execution::seq;

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
        return std::transform_reduce(execution, lines.begin(), lines.end(), 0L, std::plus{}, [](const auto &line) {
            return JoltageMeter::maxDoubleDigit(line);
        });
    }

    size_t exercise2(const std::vector<std::string> &lines) {
        return std::transform_reduce(execution, lines.begin(), lines.end(), 0, std::plus{}, [](const auto &line) {
            return JoltageMeter::maxTwelveDigit(line);
        });
    }
} // namespace

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
