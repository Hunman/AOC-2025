#include "day4/room.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <ranges>

namespace {
    constexpr auto execution1 = std::execution::unseq;
    constexpr auto execution2 = std::execution::par;

    std::vector<std::string> getLines() {
        std::ifstream in{std::filesystem::path(INPUT_DIRECTORY) / "day4.txt"};

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

    size_t exercise1(const std::vector<std::string> &lines) {
        Room room{lines};

        auto rows = std::views::iota(0, static_cast<int32_t>(room.rows()));
        return std::transform_reduce(execution1, rows.begin(), rows.end(), 0uz, std::plus{}, [&room](int32_t y) -> size_t {
            auto columns = std::views::iota(0, static_cast<int32_t>(room.columns()));
            return std::transform_reduce(execution1, columns.begin(), columns.end(), 0uz, std::plus{}, [&room, y](int32_t x) -> size_t {
                return room[x, y].isRemovable();
            });
        });
    }

    size_t exercise2(const std::vector<std::string> &lines) {
        Room room{lines};

        auto totalRemoved = 0uz;
        auto removed = 0uz;

        do {
            auto rows = std::views::iota(0, static_cast<int32_t>(room.rows()));
            removed = std::transform_reduce(execution2, rows.begin(), rows.end(), 0uz, std::plus{}, [&room](int32_t y) -> size_t {
                auto columns = std::views::iota(0, static_cast<int32_t>(room.columns()));
                return std::transform_reduce(execution2, columns.begin(), columns.end(), 0uz, std::plus{}, [&room, y](int32_t x) -> size_t {
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
} // namespace

int main() {
    run<4, getLines, exercise1, exercise2>();

    return 0;
}
