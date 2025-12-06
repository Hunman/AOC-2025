#include "day6/cephaloproblem.hpp"
#include "day6/problem.hpp"
#include "gtest/gtest.h"

TEST(Day6Test, Exercise1GivenExampleTest) {
    using Problem = Problem<3>;

    {
        Problem problem{{123, 45, 6}, Problem::Operation::MULTIPLY};
        ASSERT_EQ(33210, problem.result());
    }
    {
        Problem problem{{328, 64, 98}, Problem::Operation::PLUS};
        ASSERT_EQ(490, problem.result());
    }
    {
        Problem problem{{51, 387, 215}, Problem::Operation::MULTIPLY};
        ASSERT_EQ(4243455, problem.result());
    }
    {
        Problem problem{{64, 23, 314}, Problem::Operation::PLUS};
        ASSERT_EQ(401, problem.result());
    }
}

TEST(Day6Test, Exercise2SingleGivenExample1Test) {
    using CephaloProblem = CephaloProblem<3>;

    CephaloProblem problem{};
    problem.addLines({
        "123",
        " 45",
        "  6",
        "*  ",
    });

    ASSERT_EQ(8544, problem.result());
}

TEST(Day6Test, Exercise2SingleGivenExample2Test) {
    using CephaloProblem = CephaloProblem<3>;

    CephaloProblem problem{};
    problem.addLines({
        "328",
        "64 ",
        "98 ",
        "+  ",
    });

    ASSERT_EQ(625, problem.result());
}

TEST(Day6Test, Exercise2SingleGivenExample3Test) {
    using CephaloProblem = CephaloProblem<3>;

    CephaloProblem problem{};
    problem.addLines({
        " 51",
        "387",
        "215",
        "*  ",
    });

    ASSERT_EQ(3253600, problem.result());
}

TEST(Day6Test, Exercise2SingleGivenExample4Test) {
    using CephaloProblem = CephaloProblem<3>;

    CephaloProblem problem{};
    problem.addLines({
        "64 ",
        "23 ",
        "314",
        "+  ",
    });

    ASSERT_EQ(1058, problem.result());
}

TEST(Day6Test, Exercise2GivenExampleTest) {
    using CephaloProblem = CephaloProblem<3>;

    CephaloProblem problem{};
    problem.addLines({
        "123 328  51 64 ",
        " 45 64  387 23 ",
        "  6 98  215 314",
        "*   +   *   +  ",
    });

    ASSERT_EQ(3263827, problem.result());
}