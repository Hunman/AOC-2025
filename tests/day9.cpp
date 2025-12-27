#include "day9/movie_theatre.hpp"
#include "gtest/gtest.h"

TEST(Day9Test, GivenExercise1Test) {
    std::vector<MovieTheatre::Coordinate> coordinates({
        {7, 1},
        {11, 1},
        {11, 7},
        {9, 7},
        {9, 5},
        {2, 5},
        {2, 3},
        {7, 3},
    });

    ASSERT_EQ(50, MovieTheatre::exercise1(coordinates));
}

TEST(Day9Test, GivenExercise2Test) {
    auto coordinates = std::to_array<MovieTheatre::Coordinate>({
        {7, 1},
        {11, 1},
        {11, 7},
        {9, 7},
        {9, 5},
        {2, 5},
        {2, 3},
        {7, 3},
    });

    ASSERT_EQ(24, MovieTheatre::exercise2(coordinates));
}
