#pragma once
#include <algorithm>

template <typename T>
concept IsLessComparable = requires(T a, T b) {
    a < b;
};

struct Minimum {
    template <typename T> requires IsLessComparable<T>
    constexpr T operator()(const T &a, const T &b) const {
        return std::min(a, b);
    }
};
