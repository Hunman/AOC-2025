#include "day4/room.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <ranges>

class Day4: public Day<4> {
public:
    static constexpr auto execution1 = std::execution::unseq;
    static constexpr auto execution2 = std::execution::par;

    using Line = std::string;
    using Input = std::vector<Line>;

    static Input getInput() {
        std::ifstream in{getInputPath()};

        auto lineCount = 0uz;
        for (std::string line; std::getline(in, line);) {
            lineCount++;
        }

        Input lines{lineCount};
        in.clear();
        in.seekg(0);

        for (size_t i = 0uz; i < lineCount; i++) {
            std::getline(in, lines[i]);
        }

        return lines;
    }

    static uint64_t exercise1(const Input &lines) {
        Room room{lines};

        auto rows = std::views::iota(0, static_cast<int32_t>(room.rows()));
        return std::transform_reduce(execution1, rows.begin(), rows.end(), 0uz, std::plus{}, [&room](int32_t y) -> uint64_t {
            auto columns = std::views::iota(0, static_cast<int32_t>(room.columns()));
            return std::transform_reduce(execution1, columns.begin(), columns.end(), 0uz, std::plus{}, [&room, y](int32_t x) -> uint64_t {
                return room[x, y].isRemovable();
            });
        });
    }

    static uint64_t exercise2(const Input &lines) {
        Room room{lines};

        auto totalRemoved = 0uz;
        auto removed = 0uz;

        do {
            auto rows = std::views::iota(0, static_cast<int32_t>(room.rows()));
            removed = std::transform_reduce(execution2, rows.begin(), rows.end(), 0uz, std::plus{}, [&room](int32_t y) -> uint64_t {
                auto columns = std::views::iota(0, static_cast<int32_t>(room.columns()));
                return std::transform_reduce(execution2, columns.begin(), columns.end(), 0uz, std::plus{}, [&room, y](int32_t x) -> uint64_t {
                    auto cell = room[x, y];
                    if (!cell.isRemovable()) {
                        return false;
                    }

                    cell.remove();
                    return true;
                });
            });

            room.remove();

            totalRemoved += removed;
        } while (removed > 0uz);

        return totalRemoved;
    }
};

int main() {
    Framework<Day4>::run();

    return 0;
}
