#include "day8/junction_box.hpp"

#include "day8/circuit.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <numeric>

JunctionBox::JunctionBox(uint64_t x, uint64_t y, uint64_t z): x(x), y(y), z(z) {}

double JunctionBox::distanceSquared(const JunctionBox &other) {
    auto d = [](uint64_t d) {
        return static_cast<double>(d);
    };
    return square(d(this->x) - d(other.x)) + square(d(this->y) - d(other.y)) + square(d(this->z) - d(other.z));
}

JunctionBox *JunctionBox::moveTo(Circuit *connection) {
    this->connection->remove(this);
    this->connection = connection;

    return this;
}

void JunctionBox::connect(JunctionBox &box) {
    if (connection == box.connection) {
        return;
    }

    connection->merge(box.connection);
}

uint64_t JunctionBox::exercise1(std::vector<JunctionBox> input, size_t connectionCount, size_t largestJunctions) {
    // Pointers because I will need to sort them by number of JunctionBoxes inside
    std::vector<std::unique_ptr<Circuit>> connections{input.size()};
    for (size_t i = 0uz; i < input.size(); i++) {
        connections[i] = std::make_unique<Circuit>(&input[i]);
        input[i].connection = connections[i].get();
    }

    constexpr double infinity = std::numeric_limits<double>::infinity();

    // I am wasting space, I know
    std::vector<double> distances(input.size() * input.size());

    auto width = input.size();
    auto index = [width](uint64_t x, uint64_t y) -> uint64_t {
        return y * width + x;
    };
    auto coord = [width](uint64_t index) {
        return std::make_pair(index / width, index % width);
    };

    for (uint64_t x = 0; x < input.size(); x++) {
        for (uint64_t y = 0; y < input.size(); y++) {
            if (x == y) { // Never connect a node with itself
                distances[index(x, y)] = infinity;
                continue;
            }
            distances[index(x, y)] = distances[index(y, x)] = input[x].distanceSquared(input[y]);
        }
    }

    for (size_t i = 0; i < connectionCount; i++) {
        auto minDistance = std::min_element(distances.begin(), distances.end(), [](double a, double b) {
            return a < b;
        });
        auto minIndex = std::distance(distances.begin(), minDistance);
        auto [x, y] = coord(minIndex);
        input[x].connect(input[y]);
        distances[index(x, y)] = infinity;
        distances[index(y, x)] = infinity;
    }

    std::stable_sort(connections.begin(), connections.end(), [](const auto &a, const auto &b) {
        return a->size() > b->size();
    });

    return std::transform_reduce(
        connections.begin(),
        connections.begin() + largestJunctions,
        1ull,
        std::multiplies{},
        [](const auto &connection) {
            return connection->size();
        }
    );
}

uint64_t JunctionBox::exercise2(std::vector<JunctionBox> input) {
    // Pointers because I will need to sort them by number of JunctionBoxes inside
    std::vector<std::unique_ptr<Circuit>> connections{input.size()};
    for (size_t i = 0uz; i < input.size(); i++) {
        connections[i] = std::make_unique<Circuit>(&input[i]);
        input[i].connection = connections[i].get();
    }

    constexpr double infinity = std::numeric_limits<double>::infinity();

    // I am wasting space, I know
    std::vector<double> distances(input.size() * input.size());

    auto width = input.size();
    auto index = [width](uint64_t x, uint64_t y) -> uint64_t {
        return y * width + x;
    };
    auto coord = [width](uint64_t index) {
        return std::make_pair(index / width, index % width);
    };

    for (uint64_t x = 0; x < input.size(); x++) {
        for (uint64_t y = 0; y < input.size(); y++) {
            if (x == y) { // Never connect a node with itself
                distances[index(x, y)] = infinity;
                continue;
            }
            distances[index(x, y)] = distances[index(y, x)] = input[x].distanceSquared(input[y]);
        }
    }

    size_t lastX, lastY, targetSize = 0uz;
    do {
        auto minDistance = std::min_element(distances.begin(), distances.end(), [](double a, double b) {
            return a < b;
        });
        auto minIndex = std::distance(distances.begin(), minDistance);
        auto [x, y] = coord(minIndex);
        input[x].connect(input[y]);
        targetSize = input[x].connection->size();
        lastX = x;
        lastY = y;
        distances[index(x, y)] = infinity;
        distances[index(y, x)] = infinity;
    } while (targetSize != input.size());

    return input[lastX].x * input[lastY].x;
}

double JunctionBox::square(double p) {
    return p * p;
}
