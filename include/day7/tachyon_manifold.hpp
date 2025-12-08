#pragma once
#include <execution>
#include <iostream>
#include <string>
#include <vector>

namespace TachyonManifold {
    static constexpr auto SPLITTER = '^';

    static constexpr uint64_t exercise1(const auto &input) {
        std::vector<bool> beams(input[0].length());

        beams[input[0].find('S')] = true;
        auto splits = 1ull;

        for (size_t l = 1; l < input.size(); l++) {
            for (size_t i = 0; i < input[l].size(); i++) {
                if (input[l][i] == SPLITTER && beams[i]) {
                    beams[i] = false;
                    if (!beams[i - 1]) {
                        beams[i - 1] = true;
                        splits++;
                    }
                    if (!beams[i + 1]) {
                        beams[i + 1] = true;
                        splits++;
                    }
                }
            }
        }

        return splits - std::count(beams.begin(), beams.end(), true);
    }

    static constexpr uint64_t exercise2(const auto &input) {
        std::vector<uint64_t> beams(input[0].length());

        beams[input[0].find('S')] = true;

        for (size_t l = 1; l < input.size(); l++) {
            for (size_t i = 0; i < input[l].size(); i++) {
                if (input[l][i] == SPLITTER && beams[i]) {
                    beams[i - 1] += beams[i];
                    beams[i + 1] += beams[i];
                    beams[i] = 0;
                }
            }
        }

        return std::reduce(beams.begin(), beams.end(), 0ull, std::plus{});
    }
};
