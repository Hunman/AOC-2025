#include "day8/junction_box.hpp"
#include "framework.hpp"

#include <fstream>
#include <ranges>
#include <vector>

class Day8: public Day<8> {
public:
    static auto getInput() {
        using std::string_view_literals::operator ""sv;
        std::ifstream in{getInputPath()};

        auto lineCount = 0uz;
        for (std::string line; std::getline(in, line);) {
            lineCount++;
        }

        std::vector<JunctionBox> boxes;
        boxes.reserve(lineCount);
        in.clear();
        in.seekg(0);

        std::string line;
        for (size_t i = 0uz; i < lineCount; i++) {
            std::getline(in, line);
            std::array<uint64_t, 3> coords;
            for (size_t c = 0uz; const auto coord: std::views::split(line, ","sv)) {
                auto sv = std::string_view(coord);
                coords[c++] = std::stoull(sv.data());
            }
            boxes.emplace_back(coords[0], coords[1], coords[2]);
        }

        return boxes;
    }

    static constexpr uint64_t exercise1(const auto &input) {
        return JunctionBox::exercise1(input, 1000, 3);
    }

    static constexpr uint64_t exercise2(const auto &input) {
        return JunctionBox::exercise2(input);
    }
};

int main() {
    Framework<Day8>::run();

    return 0;
}
