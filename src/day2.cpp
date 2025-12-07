#include "day2/invalid_finder.hpp"
#include "day2/range.hpp"
#include "framework.hpp"

#include <execution>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <vector>

class Day2: public Day<2> {
public:
    static constexpr auto execution = std::execution::par_unseq;

    using Input = std::vector<Range>;

    static Input getInput() {
        using std::string_view_literals::operator""sv;

        std::ifstream in{getInputPath()};
        std::string fileContent;
        std::getline(in, fileContent);

        Input ret;

        for (const auto line: std::views::split(fileContent, ","sv)) {
            auto sv = std::string_view(line);
            auto start = std::stoull(&sv[0]);
            auto end = std::stoull(&(sv[sv.find('-') + 1]));

            ret.emplace_back(start, end);
        }

        return ret;
    }

    static uint64_t exercise1(const Input &intervals) {
        return std::transform_reduce(
            execution,
            intervals.begin(),
            intervals.end(),
            0ull,
            std::plus{},
            [](const Range &interval) {
                auto range = std::views::iota(interval.start, interval.end + 1);
                return std::transform_reduce(execution, range.begin(), range.end(), 0L, std::plus{}, [](const auto i) {
                    return InvalidFinder::checkTwice(i) ? i : 0;
                });
            }
        );
    }

    static uint64_t exercise2(const Input &intervals) {
        return std::transform_reduce(
            execution,
            intervals.begin(),
            intervals.end(),
            0ull,
            std::plus{},
            [](const Range &interval) {
                auto range = std::views::iota(interval.start, interval.end + 1);
                return std::transform_reduce(execution, range.begin(), range.end(), 0L, std::plus{}, [](const auto i) {
                    return InvalidFinder::checkAtLeastTwice(i) ? i : 0;
                });
            }
        );
    }
};

int main() {
    Framework<Day2>::run();

    return 0;
}
