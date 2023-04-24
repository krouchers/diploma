#include "gtest/gtest.h"
#include "math/vec4.hpp"
#include "math/mat4x4.hpp"
#include "math/transforms.hpp"

#include <cmath>

int main()
{
    testing::InitGoogleTest();
    [[maybe_unused]] int a{RUN_ALL_TESTS()};
}

TEST(vector_test, num_multiplication)
{
    math::Vec4 v{1, 1, 1, 1};
    math::Vec4 expected{3, 3, 3, 3};
    EXPECT_EQ(3.0f * v, expected);
}

TEST(vector_mat_test, multiplication)
{
    math::Vec4 v{1, 2, 3, 4};
    math::Mat4x4 I{1, 2, 3, 4,
                   5, 6, 7, 8,
                   9, 10, 11, 12,
                   13, 14, 15, 16};

    math::Vec4 expected{30, 70, 110, 150};
    EXPECT_EQ(I * v, expected);
}

TEST(matrix_test, num_multiplication)
{
    math::Mat4x4 I{};
    math::Mat4x4 expected{
        3, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 3, 0,
        0, 0, 0, 3};

    EXPECT_EQ(3.0f * I, expected);
}

TEST(matrix_test, multiplication)
{
    math::Mat4x4 I1{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16};
    math::Mat4x4 I2{
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16};

    math::Mat4x4 expected{90, 100, 110, 120,
                          202, 228, 254, 280,
                          314, 356, 398, 440,
                          426, 484, 542, 600};

    EXPECT_EQ(I1 * I2, expected);
}

TEST(matrix_test, inverse)
{
    math::Mat4x4 I1{1, 2, 3, 4,
                    45, 56, 76, 8,
                    9, 11, 11, 11,
                    12, 12, 12, 43};
    math::Mat4x4 expected{-(647. + 6173.) / 6173., 341. / 6173., -1552. / 6173., 968. / 6173,
                          4227. / 6173., -520. / 6173., 3833. / 6173., -1277 / 6173.,
                          873. / 6173., 265. / 6173., -1894. / 6173., 354. / 6173.,
                          480. / 6173., -24. / 6173., -108. / 6173., 131. / 6173.};
    auto a = I1.Inverse();
    EXPECT_EQ(a, expected);
}

TEST(matrix_test, translation)
{
    math::Vec4 v{1, 1, 1, 1};
    math::Mat4x4 t_mat{math::Translate({2, 2, 2})};
    math::Vec4 expected{3, 3, 3, 1};
    EXPECT_EQ(t_mat * v, expected);
}

TEST(matrix_test, get_projection_matrix)
{
    math::Mat4x4 mat = math::Perspective(2.f, 10, 45, 720. / 1280.);
    math::Vec4 vertex{-0.5f, -0.5f, -10.0f, 1.f};
    math::Vec4 transformed{mat * vertex};
    math::Vec4 expected{-0.5, -0.888889, 10, 10};
    EXPECT_EQ(transformed, expected);
}