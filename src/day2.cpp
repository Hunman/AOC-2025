#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

#include "stopwatch.hpp"
#include "day2/invalid_finder.hpp"
#include "day2/range.hpp"

namespace {
    std::vector<Range> getIntervals() {
        using std::string_view_literals::operator ""sv;

        std::ifstream in{std::filesystem::path(INPUT_DIRECTORY) / "day2.txt"};
        std::string fileContent;
        std::getline(in, fileContent);

        std::vector<Range> ret;

        for (const auto line : std::views::split(fileContent, ","sv)) {
            auto sv = std::string_view(line);
            auto start = std::stoull(&sv[0]);
            auto end = std::stoull(&(sv[sv.find('-') + 1]));

            ret.emplace_back(start, end);
        }

        return ret;
    }

    size_t exercise1(const std::vector<Range> intervals) {
        auto sums = 0uz;

        for (const auto &interval: intervals) {
            for (auto i = interval.start; i <= interval.end; i++) {
                if (InvalidFinder::checkTwice(i)) {
                    sums += i;
                }
            }
        }

        return sums;
    }

    size_t exercise2(const std::vector<Range> intervals) {
        auto sums = 0uz;

        for (const auto &interval: intervals) {
            for (auto i = interval.start; i <= interval.end; i++) {
                if (InvalidFinder::checkAtLeastTwice(i)) {
                    sums += i;
                }
            }
        }

        return sums;
    }
};

int main() {
    std::printf("[Parsing inputs]\n");
    auto intervals = stopwatch("   ", [] {
        return getIntervals();
    });

    std::printf("\n[Exercise 1]\n");
    auto e1 = stopwatch("   ", [&intervals] {
        return exercise1(intervals);
    });
    std::printf("    the result is %lu\n", e1);

    std::printf("\n[Exercise 2]\n");
    auto e2 = stopwatch("   ", [&intervals] {
        return exercise2(intervals);
    });
    std::printf("    the result is %lu\n", e2);

    return 0;
}
