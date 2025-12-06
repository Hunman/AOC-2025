#pragma once
#include <array>
#include <cstdint>
#include <numeric>
#include <string>
#include <vector>

template <size_t S>
class CephaloProblem {
public:
    using Line = std::string;
    using Lines = std::array<Line, S + 1>;

    CephaloProblem() = default;

    void addLines(const Lines &lines) {
        this->lines = lines;
    }

    u_int64_t result() const {
        auto result = 0ull;

        std::vector<uint64_t> numbers;
        char operation;
        for (size_t i = 0; i <= lines[0].length(); i++) {
            uint64_t number = 0ull;

            if (char c = lines[S][i]; c != ' ' && c != '\0') {
                operation = lines[S][i];
            }
            for (size_t l = 0; l < S; l++) {
                if (char c = lines[l][i]; c != ' ' && c != '\0') {
                    number *= 10;
                    number += (c - '0');
                }
            }
            if (number != 0) {
                numbers.push_back(number);
                continue;
            }
            result += evaluate(operation, numbers);
            numbers.clear();
        }

        return result;
    }

private:
    Lines lines;

    static uint64_t evaluate(char operation, const std::vector<uint64_t> numbers) {
        auto result = [&numbers](auto operation, uint64_t init) -> uint64_t {
            return std::reduce(numbers.begin(), numbers.end(), init, operation);
        };

        if (operation == '+') {
            return result(std::plus<uint64_t>{}, 0ull);
        }

        return result(std::multiplies<uint64_t>{}, 1ull);
    }
};