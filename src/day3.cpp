#include "day3/joltage_meter.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <ranges>

class Day3: public Day<3> {
public:
    static constexpr auto execution = std::execution::seq;

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
        return std::transform_reduce(execution, lines.begin(), lines.end(), 0ull, std::plus{}, [](const auto &line) {
            return JoltageMeter::maxDoubleDigit(line);
        });
    }

    static uint64_t exercise2(const Input &lines) {
        return std::transform_reduce(execution, lines.begin(), lines.end(), 0ull, std::plus{}, [](const auto &line) {
            return JoltageMeter::maxTwelveDigit(line);
        });
    }
};

int main() {
    Framework<Day3>::run();

    return 0;
}
