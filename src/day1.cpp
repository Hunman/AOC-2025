#include "day1/dial.h"
#include "framework.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class Day1: public Day<1> {
public:
    using Line = std::string;
    using Input = std::vector<Line>;

    static Input getInput() {
        std::ifstream in{getInputPath()};

        auto lineCount = 0uz;
        for (std::string line; std::getline(in, line);) {
            lineCount++;
        }

        Input lines{lineCount};
        in.clear();
        in.seekg(0);

        for (size_t i = 0uz; i < lineCount; i++) {
            std::getline(in, lines[i]);
        }

        return lines;
    }

    static uint64_t exercise1(const Input &lines) {
        Dial dial{50, 100};

        auto zeros = 0ull;
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

    static uint64_t exercise2(const Input &lines) {
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
};

int main() {
    Framework<Day1>::run();

    return 0;
}
