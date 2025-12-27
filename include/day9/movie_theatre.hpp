#pragma once
#include <algorithm>
#include <cstdint>
#include <functional>
#include <numeric>
#include <ranges>
#include <vector>

namespace MovieTheatre {
    struct Coordinate {
        uint64_t x, y;

        constexpr bool operator==(const auto &o) const {
            return x == o.x && y == o.y;
        }
    };

    static constexpr uint64_t getArea(const Coordinate &a, const Coordinate &b) {
        return (std::max(a.x, b.x) - std::min(a.x, b.x) + 1) * (std::max(a.y, b.y) - std::min(a.y, b.y) + 1);
    }

    static constexpr auto max() {
        return [](const auto &a, const auto &b) -> uint64_t {
            return std::max(a, b);
        };
    }

    constexpr uint64_t exercise1(const auto &input) {
        auto range = std::views::iota(0uz, input.size() - 1uz);
        return std::transform_reduce(range.begin(), range.end(), 0uz, max(), [&input](size_t a) -> uint64_t {
            auto range = std::views::iota(a + 1uz, input.size());
            return std::transform_reduce(range.begin(), range.end(), 0uz, max(), [&input, a](size_t b) -> uint64_t {
                return getArea(input[a], input[b]);
            });
        });
    }

    constexpr uint64_t exercise2(const auto &input) {
        auto range = std::views::iota(0uz, input.size() - 1uz);
        return std::transform_reduce(range.begin(), range.end(), 0uz, max(), [&input](size_t a) -> uint64_t {
            auto range = std::views::iota(a + 1uz, input.size());
            return std::transform_reduce(range.begin(), range.end(), 0uz, max(), [&input, a](size_t b) -> uint64_t {
                Coordinate ac = input[a], bc = input[b];
                auto minX = std::min(ac.x, bc.x);
                auto maxX = std::max(ac.x, bc.x);
                auto minY = std::min(ac.y, bc.y);
                auto maxY = std::max(ac.y, bc.y);

                // Go through every single segment to check if they intersect
                for (size_t i = 0; i < input.size(); i++) {
                    Coordinate cc = input[i];
                    Coordinate dc = input[(i + 1) % input.size()];

                    // Currently selected points will always intersect
                    if ((ac == bc && cc == dc) || (ac == cc && bc == dc)) {
                        continue;
                    }

                    bool left = (cc.x <= minX && dc.x <= minX);
                    bool right = (cc.x >= maxX && dc.x >= maxX);
                    bool under = (cc.y <= minY && dc.y <= minY);
                    bool above = (cc.y >= maxY && dc.y >= maxY);
                    if (left || right || above || under) {
                        continue;
                    }

                    return 0ull;
                }

                return getArea(ac, bc);
            });
        });
    }
} // namespace MovieTheatre
