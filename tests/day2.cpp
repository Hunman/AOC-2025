#include "gtest/gtest.h"
#include "day2/invalid_finder.hpp"

class Exercise1InvalidTest: public testing::TestWithParam<uint64_t> {};

class Exercise1InvalidLengthTest: public testing::TestWithParam<uint64_t> {};

class Exercise1ValidTest: public testing::TestWithParam<uint64_t> {};

class Exercise2InvalidTest: public testing::TestWithParam<uint64_t> {};

class Exercise2ValidTest: public testing::TestWithParam<uint64_t> {};

TEST_P(Exercise1InvalidTest, RecognizesInvalids) {
    ASSERT_TRUE(InvalidFinder::checkTwice(GetParam()));
}

TEST_P(Exercise1InvalidLengthTest, RecognizesOddLengthAsValid) {
    ASSERT_FALSE(InvalidFinder::checkTwice(GetParam()));
}

TEST_P(Exercise1ValidTest, RecognizesValids) {
    ASSERT_FALSE(InvalidFinder::checkTwice(GetParam()));
}

TEST_P(Exercise2InvalidTest, RecognizesInvalids) {
    ASSERT_TRUE(InvalidFinder::checkAtLeastTwice(GetParam()));
}


TEST_P(Exercise2ValidTest, RecognizesValids) {
    ASSERT_FALSE(InvalidFinder::checkAtLeastTwice(GetParam()));
}


INSTANTIATE_TEST_SUITE_P(Exercise1,
                         Exercise1InvalidTest,
                         testing::Values(11, 22, 55, 1111, 1212, 4242, 100100, 123123, 6942069420)
);

INSTANTIATE_TEST_SUITE_P(Exercise1, Exercise1InvalidLengthTest, testing::Values(3, 101, 123, 12345));

INSTANTIATE_TEST_SUITE_P(Exercise1, Exercise1ValidTest, testing::Values(12, 45, 123456, 6996));

INSTANTIATE_TEST_SUITE_P(Exercise2,
                         Exercise2InvalidTest,
                         testing::Values(11, 22, 111, 999, 1010, 1188511885, 222222, 446446, 38593859, 565656, 824824824, 2121212121)
);

INSTANTIATE_TEST_SUITE_P(Exercise2, Exercise2ValidTest, testing::Values(12, 45, 123456, 6996));
