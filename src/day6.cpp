#include "day6/cephaloproblem.hpp"
#include "day6/problem.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <functional>

namespace {
    constexpr auto PROBLEM_SIZE = 4uz;
    constexpr auto PROBLEM_COUNT = 1000uz;
    constexpr auto execution = std::execution::seq;

    struct Input {
        std::vector<Problem<PROBLEM_SIZE>> day1;
        CephaloProblem<PROBLEM_SIZE> day2;
    };

    Input getLines() {
        std::ifstream in{std::filesystem::path(INPUT_DIRECTORY) / "day6.txt"};

        Input input{};
        input.day1.resize(PROBLEM_COUNT);

        for (auto l = 0uz; l < PROBLEM_SIZE; l++) {
            for (auto i = 0uz; i < PROBLEM_COUNT; i++) {
                in >> input.day1[i].numbers[l];
            }
        }
        for (auto i = 0uz; i < PROBLEM_COUNT; i++) {
            char operation;
            in >> operation;
            input.day1[i].operation = static_cast<decltype(input.day1[i].operation)>(operation);
        }

        in.clear();
        in.seekg(0);

        decltype(input.day2)::Lines lines;
        for (auto &line: lines) {
            std::getline(in, line);
        }
        input.day2.addLines(lines);

        return input;
    }

    uint64_t exercise1(const Input &input) {
        return std::transform_reduce(
            execution,
            input.day1.begin(),
            input.day1.end(),
            0uz,
            std::plus{},
            [](const Problem<PROBLEM_SIZE> &problem) {
                return problem.result();
            }
        );
    }

    uint64_t exercise2(const Input &input) {
        return input.day2.result();
    }
} // namespace

int main() {
    run<6, getLines, exercise1, exercise2>();

    return 0;
}
