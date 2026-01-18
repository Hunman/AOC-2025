#include "day7/tachyon_manifold.hpp"
#include "framework.hpp"

#include <filesystem>
#include <fstream>

class Day7: public Day<7> {
public:
    static auto getInput() {
        std::ifstream in{getInputPath()};

        auto lineCount = 0uz;
        for (std::string line; std::getline(in, line);) {
            lineCount++;
        }

        std::vector<std::string> lines{lineCount};
        in.clear();
        in.seekg(0);

        for (size_t i = 0uz; i < lineCount; i++) {
            std::getline(in, lines[i]);
        }

        return lines;
    }

    #if __has_include("day7.hpp")
    #define HAS_COMPILE_TIME_AVAILABLE_INPUT
    static consteval auto getConstInput() {
        return std::to_array<std::string_view>({
            #include "day7.hpp"
        });
    }
    #endif

    static constexpr uint64_t exercise1(const auto &input) {
        return TachyonManifold::exercise1(input);
    }

    static constexpr uint64_t exercise2(const auto &input) {
        return TachyonManifold::exercise2(input);
    }
};

int main() {
    #if defined HAS_COMPILE_TIME_AVAILABLE_INPUT
        Framework<Day7>::crun();
    #else
        Framework<Day7>::run();
    #endif

    return 0;
}
