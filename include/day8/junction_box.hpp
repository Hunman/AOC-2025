#pragma once

#include <cstdint>
#include <vector>

class Circuit;

class JunctionBox {
public:
    JunctionBox() = delete;

    JunctionBox(uint64_t x, uint64_t y, uint64_t z);

    // Normally this would be square rooted, but for comparison only this is fine
    double distanceSquared(const JunctionBox &other);

    const uint64_t x, y, z;

    JunctionBox *moveTo(Circuit *connection);

    void connect(JunctionBox &box);

    static uint64_t exercise1(std::vector<JunctionBox> input, size_t connectionCount, size_t largestJunctions);

    static uint64_t exercise2(std::vector<JunctionBox> input);

private:
    static double square(double p);

    Circuit *connection;
};
