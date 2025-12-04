#pragma once
#include "watch.hpp"

template <auto L, auto F>
concept CanBeFedInto = requires() {
    F(L());
};

template <size_t D, auto L, auto E1, auto E2> requires CanBeFedInto<L, E1> && CanBeFedInto<L, E2>
void run() {
    std::printf("[Day %zu]\n", D);

    printf("Reading input\n");
    auto input = ([]() {
        Watch watch;
        return L();
    })();

    printf("Exercise 1\n");
    auto r1 = ([](const auto &input) {
        Watch watch;
        return E1(input);
    })(input);
    std::cout << "    Result: " << r1 << "\n";

    printf("Exercise 2\n");
    auto r2 = ([](const auto &input) {
        Watch watch;
        return E2(input);
    })(input);
    std::cout << "    Result: " << r2 << "\n";
}
