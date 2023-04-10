#include "gtest/gtest.h"

#include "math.hpp"

int main()
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}

TEST(math, matrix_multiplication)
{
    mat4x4 I1, I2;
    EXPECT_EQ(I1 * I2, I1);
}