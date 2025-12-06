#pragma once
#include <array>
#include <cstdint>
#include <numeric>

template <std::size_t S>
struct Problem {
    using Type = uint64_t;

    std::array<Type, S> numbers;

    enum class Operation : char {
        PLUS = '+',
        MULTIPLY = '*',
    } operation;

    uint64_t result() const {
        auto result = [this](auto operation, uint64_t init) -> uint64_t {
            return std::reduce(numbers.begin(), numbers.end(), init, operation);
        };

        if (operation == Operation::PLUS) {
            return result(std::plus<Type>{}, 0ull);
        }

        return result(std::multiplies<Type>{}, 1ull);
    }
};
