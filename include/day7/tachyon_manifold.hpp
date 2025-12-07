#pragma once
#include <execution>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class TachyonManifold {
public:
    using Line = std::string;
    using Input = std::vector<Line>;

    static constexpr auto SPLITTER = '^';

    TachyonManifold() = delete;

    explicit TachyonManifold(Input &&input);

    uint64_t exercise1() const {
        std::set<uint64_t> beams;

        beams.insert(input[0].find('S'));
        auto splits = 1ull;

        for (size_t l = 1; l < input.size(); l++) {
            for (size_t i = 0; i < input[l].size(); i++) {
                if (input[l][i] == SPLITTER && beams.contains(i)) {
                    beams.erase(i);
                    splits += beams.insert(i - 1).second;
                    splits += beams.insert(i + 1).second;
                }
            }
        }

        return splits - beams.size();
    }

    uint64_t exercise2() const {
        using Map = std::map<uint64_t, uint64_t>;
        Map beams;

        beams[input[0].find('S')] = 1;

        for (size_t l = 1; l < input.size(); l++) {
            for (size_t i = 0; i < input[l].size(); i++) {
                if (input[l][i] == SPLITTER && beams.contains(i)) {
                    beams[i - 1] += beams[i];
                    beams[i + 1] += beams[i];
                    beams.erase(i);
                }
            }
        }

        return std::transform_reduce(beams.begin(), beams.end(), 0ull, std::plus{}, [](const Map::value_type &pair) {
            return pair.second;
        });
    }

private:
    Input input;
};
