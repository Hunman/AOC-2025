#include "day5/interval.hpp"
#include "gtest/gtest.h"

class IntervalTester {
    static const auto &map(const Interval &interval) {
        return interval.map;
    }
};

TEST(Day5Test, DefaultTest) {
    Interval interval;

    for (size_t i = 0uz; i < 50uz; i++) {
        ASSERT_FALSE(interval[i]);
    }
}

TEST(Day5Test, AddOneTest) {
    Interval interval;

    interval.add(10, 20);

    for (size_t i = 0uz; i < 10uz; i++) {
        ASSERT_FALSE(interval[i]);
    }
    for (size_t i = 10uz; i < 20uz; i++) {
        ASSERT_TRUE(interval[i]);
    }
    for (size_t i = 20uz; i < 50uz; i++) {
        ASSERT_FALSE(interval[i]);
    }
}

TEST(Day5Test, AddTwoIndependentTest) {
    Interval interval;

    interval.add(10, 20);
    interval.add(30, 40);

    for (size_t i = 0uz; i < 10uz; i++) {
        ASSERT_FALSE(interval[i]);
    }
    for (size_t i = 10uz; i < 20uz; i++) {
        ASSERT_TRUE(interval[i]);
    }
    for (size_t i = 20uz; i < 30uz; i++) {
        ASSERT_FALSE(interval[i]);
    }
    for (size_t i = 30uz; i < 39uz; i++) {
        ASSERT_TRUE(interval[i]);
    }
    for (size_t i = 40uz; i < 50uz; i++) {
        ASSERT_FALSE(interval[i]);
    }
}

TEST(Day5Test, AddTwoOverlappingTest) {
    Interval interval;

    interval.add(10, 20);
    interval.add(15, 25);

    for (size_t i = 0uz; i < 10uz; i++) {
        ASSERT_FALSE(interval[i]);
    }
    for (size_t i = 10uz; i < 25uz; i++) {
        ASSERT_TRUE(interval[i]);
    }
    for (size_t i = 25uz; i < 50uz; i++) {
        ASSERT_FALSE(interval[i]);
    }
}

TEST(Day5Test, EmptyValidTest) {
    Interval interval;

    ASSERT_EQ(0uz, interval.getValidCount());
}

TEST(Day5Test, OneValidTest) {
    Interval interval;

    interval.add(10uz, 20uz);

    ASSERT_EQ(10uz, interval.getValidCount());
}

TEST(Day5Test, TwoValidIndependentTest) {
    Interval interval;

    interval.add(10uz, 20uz);
    interval.add(30uz, 40uz);

    ASSERT_EQ(20uz, interval.getValidCount());
}

TEST(Day5Test, TwoValidOverlappingTest) {
    Interval interval;

    interval.add(10uz, 20uz);
    interval.add(15uz, 25uz);

    ASSERT_EQ(15uz, interval.getValidCount());
}

TEST(Day5Test, GivenExampleTest) {
    Interval interval;

    interval.invlusiveAdd(3uz, 5uz);
    interval.invlusiveAdd(10uz, 14uz);
    interval.invlusiveAdd(16uz, 20uz);
    interval.invlusiveAdd(12uz, 18uz);

    ASSERT_EQ(14uz, interval.getValidCount());
}

TEST(Day5Test, RedditExampleTest) {
    Interval interval;

    interval.invlusiveAdd(1uz, 100uz);
    interval.invlusiveAdd(50uz, 51uz);

    ASSERT_EQ(100uz, interval.getValidCount());
}
