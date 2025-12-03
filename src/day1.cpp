#include "day1/dial.h"
#include "stopwatch.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {
    std::vector<std::string> getLines() {
        std::ifstream in{std::filesystem::path(INPUT_DIRECTORY) / "day1.txt"};

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
        Dial dial{50, 100};

        auto zeros = 0uz;
        for (const auto &line: lines) {
            size_t (Dial::*direction)(size_t) = &Dial::right;
            if (line[0] == 'L') {
                direction = &Dial::left;
            }
            (dial.*direction)(std::stoi(&line[1]));

            if (dial.value() == 0) {
                zeros++;
            }
        }

        return zeros;
    }

    size_t exercise2(const std::vector<std::string> &lines) {
        Dial dial{50, 100};

        auto zeros = 0uz;
        for (const auto &line: lines) {
            size_t (Dial::*direction)(size_t) = &Dial::right;
            if (line[0] == 'L') {
                direction = &Dial::left;
            }
            zeros += (dial.*direction)(std::stoi(&line[1]));
        }

        return zeros;
    }
} // namespace

int main() {
    auto lines = stopwatch("Reading the lines", [] {
        return getLines();
    });

    {
        auto e1 = stopwatch("Exercise 1", [&lines] {
            return exercise1(lines);
        });
        std::printf("Exercise 1: the dial was on zero %lu times\n", e1);
    }

    {
        auto e2 = stopwatch("Exercise 2", [&lines] {
            return exercise2(lines);
        });
        std::printf("Exercise 2: the dial hit zero %lu times\n", e2);
    }

    return 0;
}
