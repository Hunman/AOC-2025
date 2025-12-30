#pragma once
#include "function_objects.hpp"

#include <bitset>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

class MachineTester;

class Machine {
public:
    Machine() = delete;

    Machine(const std::string &line):
        lightsCount(parseLightsCount(line)),
        target(parseLights(lightsCount, line)),
        buttons{parseButtons(line)},
        joltages{parseJoltages(line)} {}

    uint64_t exercise1() const {
        size_t totalCombinations = 1 << buttons.size();
        auto combinations = std::views::iota(
            1uz, // Have to press at least 1 button
            totalCombinations
        );


        return std::transform_reduce(
            combinations.begin(),
            combinations.end(),
            totalCombinations,
            Minimum{},
            [this](size_t combination) {
                uint64_t result = 0ull;
                uint64_t lights = 0ull;

                for (size_t i = 0uz; i < buttons.size(); i++) {
                    if (combination & (1 << i)) {
                        lights++;
                        result ^= buttons[i];
                    }
                }

                return result == target ? lights : buttons.size();
            }
        );
    }

protected:
    using Lights = uint64_t;
    using Button = uint64_t;
    using Joltage = uint64_t;

    size_t lightsCount;
    const Lights target;
    const std::vector<Button> buttons;
    const std::vector<Joltage> joltages;

    static size_t parseLightsCount(const std::string &line) {
        return line.find_first_of(']') - 1;
    }

    static uint64_t parseLights(size_t count, const std::string &line) {
        uint64_t target = 0ull;

        for (size_t i = count; i > 0; i--) {
            target <<= 1;
            target += line[i] == '#';
        }

        return target;
    }

    static std::vector<Button> parseButtons(const std::string &line) {
        using std::string_view_literals::operator""sv;

        std::vector<Button> buttons;

        auto start = line.find_first_of(' ') + 1;
        std::string_view view{line.c_str() + start, line.find_last_of(' ') - start};

        for (const auto buttonString: std::views::split(view, " "sv)) {
            auto sv = std::string_view(buttonString);
            std::string_view withoutBrackets{sv.begin() + 1, sv.length() - 2};

            Button button = 0ull;
            for (const auto singleButton: std::views::split(withoutBrackets, ","sv)) {
                auto buttonView = std::string_view(singleButton);
                button ^= 1 << std::stoul(buttonView.begin());
            }
            buttons.push_back(button);
        }

        return buttons;
    }

    static std::vector<Joltage> parseJoltages(const std::string &line) {
        using std::string_view_literals::operator""sv;

        std::vector<Joltage> joltages;

        auto start = line.find_first_of('{') + 1;
        std::string_view withoutBrackets{line.c_str() + start, line.find_last_of('}') - start};

        for (const auto joltageView: std::views::split(withoutBrackets, ","sv)) {
            joltages.push_back(std::stoul(joltageView.begin()));
        }

        return joltages;
    }

    friend MachineTester;
};
