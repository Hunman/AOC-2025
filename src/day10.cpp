#include "day10/machine.hpp"
#include "framework.hpp"

#include <fstream>
#include <ranges>
#include <vector>

class Day10: public Day<10> {
public:
    static auto getInput() {
        using std::string_view_literals::operator ""sv;
        std::ifstream in{getInputPath()};

        auto lineCount = 0uz;
        for (std::string line; std::getline(in, line);) {
            lineCount++;
        }

        std::vector<Machine> machines;
        machines.reserve(lineCount);
        in.clear();
        in.seekg(0);

        std::string line;
        for (size_t i = 0uz; i < lineCount; i++) {
            std::getline(in, line);
            machines.emplace_back(line);
        }

        return machines;
    }

    static constexpr uint64_t exercise1(const auto &input) {
        return std::transform_reduce(input.begin(), input.end(), 0ull, std::plus{}, [](const Machine &machine) {
            return machine.exercise1();
        });
    }

    static constexpr uint64_t exercise2(const auto &input) {
        return 0ull;
    }
};

int main() {
    Framework<Day10>::run();

    return 0;
}
