#include "gtest/gtest.h"
#include "math/mat4x4.hpp"

TEST(Mat4x4Test, MatMulMat)
{

    math::Mat4x4 m1{1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 10, 11, 12,
                    13, 14, 15, 16};

    math::Mat4x4 m2{1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 10, 11, 12,
                    13, 14, 15, 16};

    math::Mat4x4 expected{90, 100, 110, 120,
                          202, 228, 254, 280,
                          314, 356, 398, 440,
                          426, 484, 542, 600};
    EXPECT_EQ(m1 * m2, expected);
}