#include <gtest/gtest.h>
#include "../second_lab/src/DynamicArray.h"

TEST(DynamicArrayTest, DefaultConstructor) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(DynamicArrayTest, SizeConstructor) {
    DynamicArray<int> arr(10);
    EXPECT_EQ(arr.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], 0);
    }
}

TEST(DynamicArrayTest, ElementAccess) {
    DynamicArray<int> arr(5);
    arr[0] = 42;
    arr[4] = 99;
    EXPECT_EQ(arr[0], 42);
    EXPECT_EQ(arr[4], 99);
}

TEST(DynamicArrayTest, OutOfBoundsAccess) {
    DynamicArray<int> arr(5);
    EXPECT_THROW(arr[-1], std::out_of_range);
    EXPECT_THROW(arr[5], std::out_of_range);
}