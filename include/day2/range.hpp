#pragma once
#include <cstdint>

class Range {
public:
    Range(uint64_t start, uint64_t end): start(start), end(end) {}

    const uint64_t start, end;
};
