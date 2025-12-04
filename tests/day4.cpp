#include "day4/room.hpp"
#include "gtest/gtest.h"

static Room room(std::vector<std::string>{
    "..@@.@@@@.",
    "@@@.@.@.@@",
    "@@@@@.@.@@",
    "@.@@@@..@.",
    "@@.@@@@.@@",
    ".@@@@@@@.@",
    ".@.@.@.@@@",
    "@.@@@.@@@@",
    ".@@@@@@@@.",
    "@.@.@@@.@.",
});

TEST(Day4Test, RollTest) {
    ASSERT_FALSE((room[0, 0].isRoll()));
    ASSERT_FALSE((room[1, 0].isRoll()));

    ASSERT_TRUE((room[2, 0].isRoll()));
    ASSERT_TRUE((room[3, 0].isRoll()));

    ASSERT_FALSE((room[4, 0].isRoll()));
    ASSERT_TRUE((room[5, 0].isRoll()));

    ASSERT_TRUE((room[0, 1].isRoll()));
    ASSERT_TRUE((room[1, 1].isRoll()));
}

TEST(Day4Test, SurroundTest) {
    ASSERT_FALSE((room[0, 0].isRemovable()));
    ASSERT_FALSE((room[1, 0].isRemovable()));

    ASSERT_TRUE((room[2, 0].isRemovable()));
    ASSERT_TRUE((room[3, 0].isRemovable()));

    ASSERT_FALSE((room[4, 0].isRemovable()));
    ASSERT_TRUE((room[5, 0].isRemovable()));

    ASSERT_TRUE((room[0, 1].isRemovable()));
    ASSERT_FALSE((room[1, 1].isRemovable()));
}
