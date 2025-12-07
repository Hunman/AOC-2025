#include "day7/tachyon_manifold.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>

class Day7: public Day<7> {
public:
    static constexpr auto execution = std::execution::seq;

    static TachyonManifold getInput() {
        std::ifstream in{getInputPath()};

        auto lineCount = 0uz;
        for (std::string line; std::getline(in, line);) {
            lineCount++;
        }

        TachyonManifold::Input lines{lineCount};
        in.clear();
        in.seekg(0);

        for (size_t i = 0uz; i < lineCount; i++) {
            std::getline(in, lines[i]);
        }

        return TachyonManifold{std::move(lines)};
    }

    static uint64_t exercise1(const TachyonManifold &input) {
        return input.exercise1();
    }

    static uint64_t exercise2(const TachyonManifold &input) {
        return input.exercise2();
    }
};

int main() {
    Framework<Day7>::run();

    return 0;
}
