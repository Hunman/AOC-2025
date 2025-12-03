#include "gtest/gtest.h"
#include "day3/joltage_meter.hpp"

struct Parameter {
    const uint64_t expected;
    const std::string input;
};

class Day3Exercise1Test: public testing::TestWithParam<Parameter> {};
class Day3Exercise2Test: public testing::TestWithParam<Parameter> {};

TEST_P(Day3Exercise1Test, JoltageMeterTest) {
    const auto &param = GetParam();

    auto result = JoltageMeter::maxDoubleDigit(param.input);
    ASSERT_EQ(param.expected, result) << "The JoltageMeter::maxDoubleDigits(" << param.input << ") should return "
        << param.expected << ", but it returned " << result;
}

TEST_P(Day3Exercise2Test, JoltageMeterTest) {
    const auto &param = GetParam();

    auto result = JoltageMeter::maxTwelveDigit(param.input);
    ASSERT_EQ(param.expected, result) << "The JoltageMeter::maxTwelveDigits(" << param.input << ") should return "
        << param.expected << ", but it returned " << result;
}

INSTANTIATE_TEST_SUITE_P(Exercise1,
                         Day3Exercise1Test,
                         testing::Values(
                             Parameter{98, "987654321111111"},
                             Parameter{89, "811111111111119"},
                             Parameter{78, "234234234234278"},
                             Parameter{92, "818181911112111"}
                         ),
                         [](const auto &info) {
                             return info.param.input;
                         }
);

INSTANTIATE_TEST_SUITE_P(Exercise2,
                         Day3Exercise2Test,
                         testing::Values(
                             Parameter{987654321111, "987654321111111"},
                             Parameter{811111111119, "811111111111119"},
                             Parameter{434234234278, "234234234234278"},
                             Parameter{888911112111, "818181911112111"}
                         ),
                         [](const auto &info) {
                             return info.param.input;
                         }
);
