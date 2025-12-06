#include "day5/interval.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <ranges>

namespace {
    struct Input {
        Interval valids;
        std::vector<uint64_t> ingredients;
    };

    Input getLines() {
        std::ifstream in{std::filesystem::path(INPUT_DIRECTORY) / "day5.txt"};

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

    uint64_t exercise1(const Input &input) {
        return static_cast<uint64_t>(std::count_if(
            std::execution::par,
            input.ingredients.begin(),
            input.ingredients.end(),
            [&input](uint64_t ingredient) {
                return input.valids[ingredient];
            }
        ));
    }

    uint64_t exercise2(const Input &input) {
        return input.valids.getValidCount();
    }
} // namespace

int main() {
    run<5, getLines, exercise1, exercise2>();

    return 0;
}
