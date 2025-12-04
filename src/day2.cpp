#include "day2/invalid_finder.hpp"
#include "day2/range.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <vector>

namespace {
    constexpr auto execution = std::execution::par_unseq;

    std::vector<Range> getIntervals() {
        using std::string_view_literals::operator""sv;

        std::ifstream in{std::filesystem::path(INPUT_DIRECTORY) / "day2.txt"};
        std::string fileContent;
        std::getline(in, fileContent);

        std::vector<Range> ret;

        for (const auto line: std::views::split(fileContent, ","sv)) {
            auto sv = std::string_view(line);
            auto start = std::stoull(&sv[0]);
            auto end = std::stoull(&(sv[sv.find('-') + 1]));

            ret.emplace_back(start, end);
        }

        return ret;
    }

    size_t exercise1(const std::vector<Range> intervals) {
        return std::transform_reduce(
            execution,
            intervals.begin(),
            intervals.end(),
            0L,
            std::plus{},
            [](const Range &interval) {
                auto range = std::views::iota(interval.start, interval.end + 1);
                return std::transform_reduce(execution, range.begin(), range.end(), 0L, std::plus{}, [](const auto i) {
                    return InvalidFinder::checkTwice(i) ? i : 0;
                });
            }
        );
    }

    size_t exercise2(const std::vector<Range> intervals) {
        return std::transform_reduce(
            execution,
            intervals.begin(),
            intervals.end(),
            0L,
            std::plus{},
            [](const Range &interval) {
                auto range = std::views::iota(interval.start, interval.end + 1);
                return std::transform_reduce(execution, range.begin(), range.end(), 0L, std::plus{}, [](const auto i) {
                    return InvalidFinder::checkAtLeastTwice(i) ? i : 0;
                });
            }
        );
    }
}; // namespace

int main() {
    run<2, getIntervals, exercise1, exercise2>();

    return 0;
}
