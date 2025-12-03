#include "day1/dial.h"
#include "gtest/gtest.h"

TEST(Day1Test, OverflowReturnsToZero) {
    Dial dial{99, 100};

    dial.right(1);

    ASSERT_EQ(0, dial.value());
}

TEST(Day1Test, UnderflowReturnsToNinetyNine) {
    Dial dial{0, 100};

    dial.left(1);

    ASSERT_EQ(99, dial.value());
}

TEST(Day1Test, MultipleRotationsWork) {
    Dial dial{11, 100};

    dial.right(8);
    ASSERT_EQ(19, dial.value());

    dial.left(19);
    ASSERT_EQ(0, dial.value());
}

TEST(Day1Test, UnderflowAndOverflowBothWork) {
    Dial dial{5, 100};

    dial.left(10);
    ASSERT_EQ(95, dial.value());

    dial.right(5);
    ASSERT_EQ(0, dial.value());
}

TEST(Day1Test, Exercise2GivenExample) {
    Dial dial{50, 100};

    auto zeros = 0uz;
    {
        auto zero = dial.left(68);
        zeros += zero;
        ASSERT_EQ(82, dial.value());
        ASSERT_EQ(1, zero);
    }
    {
        auto zero = dial.left(30);
        zeros += zero;
        ASSERT_EQ(52, dial.value());
        ASSERT_EQ(0, zero);
    }
    {
        auto zero = dial.right(48);
        zeros += zero;
        ASSERT_EQ(0, dial.value());
        ASSERT_EQ(1, zero);
    }
    {
        auto zero = dial.left(5);
        zeros += zero;
        ASSERT_EQ(95, dial.value());
        ASSERT_EQ(0, zero);
    }
    {
        auto zero = dial.right(60);
        zeros += zero;
        ASSERT_EQ(55, dial.value());
        ASSERT_EQ(1, zero);
    }
    {
        auto zero = dial.left(55);
        zeros += zero;
        ASSERT_EQ(0, dial.value());
        ASSERT_EQ(1, zero);
    }
    {
        auto zero = dial.left(1);
        zeros += zero;
        ASSERT_EQ(99, dial.value());
        ASSERT_EQ(0, zero);
    }
    {
        auto zero = dial.left(99);
        zeros += zero;
        ASSERT_EQ(0, dial.value());
        ASSERT_EQ(1, zero);
    }
    {
        auto zero = dial.right(14);
        zeros += zero;
        ASSERT_EQ(14, dial.value());
        ASSERT_EQ(0, zero);
    }
    {
        auto zero = dial.left(82);
        zeros += zero;
        ASSERT_EQ(32, dial.value());
        ASSERT_EQ(1, zero);
    }

    ASSERT_EQ(6, zeros);
}

TEST(Day1Test, MultiOverflowCountsCorrectly) {
    Dial dial{50, 100};

    auto zeros = dial.right(1000);

    ASSERT_EQ(10, zeros);
}
