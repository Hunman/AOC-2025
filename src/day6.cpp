#include "day6/cephaloproblem.hpp"
#include "day6/problem.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <functional>

class Day6: public Day<6> {
public:
    static constexpr auto PROBLEM_SIZE = 4uz;
    static constexpr auto PROBLEM_COUNT = 1000uz;
    static constexpr auto execution = std::execution::seq;

    struct Input {
        std::vector<Problem<PROBLEM_SIZE>> day1;
        CephaloProblem<PROBLEM_SIZE> day2;
    };

    static Input getInput() {
        std::ifstream in{getInputPath()};

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

    static uint64_t exercise1(const Input &input) {
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

    static uint64_t exercise2(const Input &input) {
        return input.day2.result();
    }
};

int main() {
    Framework<Day6>::run();

    return 0;
}
