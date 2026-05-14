#include <gtest/gtest.h>
#include "../matrix/matrix.h"

TEST(VectorTest, Creation) {
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[0], 0);
}

TEST(VectorTest, Addition) {
    Vector<int> v1(3);
    Vector<int> v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;
    
    auto v3 = v1 + v2;
    EXPECT_EQ(v3[0], 5);
    EXPECT_EQ(v3[1], 7);
    EXPECT_EQ(v3[2], 9);
}

TEST(VectorTest, Subtraction) {
    Vector<int> v1(3);
    Vector<int> v2(3);
    v1[0] = 4; v1[1] = 5; v1[2] = 6;
    v2[0] = 1; v2[1] = 2; v2[2] = 3;
    
    auto v3 = v1 - v2;
    EXPECT_EQ(v3[0], 3);
    EXPECT_EQ(v3[1], 3);
    EXPECT_EQ(v3[2], 3);
}

TEST(VectorTest, Multiplication) {
    Vector<int> v1(3);
    Vector<int> v2(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;
    v2[0] = 4; v2[1] = 5; v2[2] = 6;
    
    auto v3 = v1 * v2; // element-wise multiplication
    EXPECT_EQ(v3[0], 4);
    EXPECT_EQ(v3[1], 10);
    EXPECT_EQ(v3[2], 18);
}