#include "day9/movie_theatre.hpp"
#include "framework.hpp"

#include <fstream>
#include <ranges>
#include <vector>

class Day9: public Day<9> {
public:
    static auto getInput() {
        using std::string_view_literals::operator ""sv;
        std::ifstream in{getInputPath()};

        auto lineCount = 0uz;
        for (std::string line; std::getline(in, line);) {
            lineCount++;
        }

        std::vector<MovieTheatre::Coordinate> coordinates;
        coordinates.reserve(lineCount);
        in.clear();
        in.seekg(0);

        std::string line;
        for (size_t i = 0uz; i < lineCount; i++) {
            std::getline(in, line);
            size_t d = 0uz;
            auto x = std::stoull(line, &d, 10);
            auto y = std::stoull(line.substr(d + 1));
            coordinates.emplace_back(x, y);
        }

        return coordinates;
    }

    static constexpr uint64_t exercise1(const auto &input) {
        return MovieTheatre::exercise1(input);
    }

    static constexpr uint64_t exercise2(const auto &input) {
        return MovieTheatre::exercise2(input);
    }
};

int main() {
    Framework<Day9>::run();

    return 0;
}
