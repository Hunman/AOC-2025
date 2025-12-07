#include "day5/interval.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <ranges>

class Day5: public Day<5> {
public:
    struct Input {
        Interval valids;
        std::vector<uint64_t> ingredients;
    };

    static Input getInput() {
        std::ifstream in{getInputPath()};

        Input input;

        auto validCount = 0uz;
        auto ingredientCount = 0uz;

        for (std::string line; std::getline(in, line);) {
            if (line.contains('-')) {
                validCount++;
            } else if (line.length()) {
                ingredientCount++;
            }
        }

        input.ingredients.reserve(ingredientCount);

        in.clear();
        in.seekg(0);

        std::string line;
        for (size_t i = 0uz; i < validCount; i++) {
            std::getline(in, line);
            size_t d = 0uz;
            auto start = std::stoull(line, &d, 10);
            auto end = std::stoull(line.substr(d + 1));
            input.valids.invlusiveAdd(start, end);
        }

        std::getline(in, line); // Empty line

        for (size_t i = 0uz; i < ingredientCount; i++) {
            std::getline(in, line);
            input.ingredients.emplace_back(std::stoull(line));
        }
        std::sort(input.ingredients.begin(), input.ingredients.end());

        return input;
    }

    static uint64_t exercise1(const Input &input) {
        return static_cast<uint64_t>(std::count_if(
            std::execution::par,
            input.ingredients.begin(),
            input.ingredients.end(),
            [&input](uint64_t ingredient) {
                return input.valids[ingredient];
            }
        ));
    }

    static uint64_t exercise2(const Input &input) {
        return input.valids.getValidCount();
    }
};

int main() {
    Framework<Day5>::run();

    return 0;
}
