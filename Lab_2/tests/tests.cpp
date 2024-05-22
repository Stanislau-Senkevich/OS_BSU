#include <gtest/gtest.h>
#include "parameters.h"

TEST(MinMaxTest, ValidInput) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int minValue = 0;
    int maxValue = 0;

    minMaxParameters params = {&nums, &minValue, &maxValue};

    EXPECT_EQ(min_max(&params), 0);
    EXPECT_EQ(minValue, 1);
    EXPECT_EQ(maxValue, 5);
}

TEST(MinMaxTest, InvalidMinValuePointer) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int* minValue = nullptr;
    int maxValue = 0;

    minMaxParameters params = {&nums, minValue, &maxValue};

    EXPECT_EQ(min_max(&params), 1);
}

TEST(MinMaxTest, InvalidMaxValuePointer) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int minValue = 0;
    int* maxValue = nullptr;

    minMaxParameters params = {&nums, &minValue, maxValue};

    EXPECT_EQ(min_max(&params), 1);
}

TEST(AverageTest, ValidInput) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    double averageValue = 0.0;

    sumParameters params = {&nums, &averageValue};

    EXPECT_EQ(average(&params), 0);
    EXPECT_DOUBLE_EQ(averageValue, 3.0);
}

TEST(AverageTest, InvalidAveragePointer) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    double* averageValue = nullptr;

    sumParameters params = {&nums, averageValue};

    EXPECT_EQ(average(&params), 1);
}

TEST(UpdateArrayTest, ValidInput) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int minValue = 1;
    int maxValue = 5;
    double avg = 3.0;

    std::vector<double> expected = {3.0, 2, 3, 4, 3.0};
    std::vector<double> result = updateArray(nums, minValue, maxValue, avg);

    EXPECT_EQ(result, expected);
}
