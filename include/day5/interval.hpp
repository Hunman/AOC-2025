#pragma once

#include <cstdint>
#include <execution>
#include <map>
#include <ranges>

class IntervalTester;

class Interval {
public:
    Interval();

    void invlusiveAdd(uint64_t start, uint64_t end) {
        add(start, end + 1); // Puzzle input is inclusive
    }

    void add(uint64_t start, uint64_t end);

    bool operator[](uint64_t key) const;

    uint64_t getValidCount() const;

private:
    std::map<uint64_t, bool> map;

    friend IntervalTester;
};
