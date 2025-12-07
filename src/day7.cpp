#include "day7/tachyon_manifold.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <functional>

namespace {
    constexpr auto execution = std::execution::seq;

    TachyonManifold getLines() {
        std::ifstream in{std::filesystem::path(INPUT_DIRECTORY) / "day7.txt"};

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

    uint64_t exercise1(const TachyonManifold &input) {
        return input.exercise1();
    }

    uint64_t exercise2(const TachyonManifold &input) {
        return input.exercise2();
    }
} // namespace

int main() {
    run<7, getLines, exercise1, exercise2>();

    return 0;
}
