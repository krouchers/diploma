#include "gtest/gtest.h"
#include "math.hpp"

#include <cmath>

int main()
{
    testing::InitGoogleTest();
    [[maybe_unused]] int a{RUN_ALL_TESTS()};
}

TEST(vector_test, num_multiplication)
{
    vec4 v{1, 1, 1, 1};
    vec4 expected{3, 3, 3, 3};
    EXPECT_EQ(3.0f * v, expected);
}

TEST(vector_mat_test, multiplication)
{
    vec4 v{1, 2, 3, 4};
    mat4x4 I{};
    EXPECT_EQ(I * v, v);
}

TEST(matrix_test, num_multiplication)
{
    mat4x4 I{};
    mat4x4 expected{
        3, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 3, 0,
        0, 0, 0, 3};

    EXPECT_EQ(3.0f * I, expected);
}

TEST(matrix_test, multiplication)
{
    mat4x4 I1, I2;
    int x{1}, y{2};
    EXPECT_EQ(I1 * I2, I1);
}

TEST(matrix_test, inverse)
{
    mat4x4 I1{1, 2, 3, 4,
              45, 56, 76, 8,
              9, 11, 11, 11,
              12, 12, 12, 43};
    mat4x4 expected{-(647. + 6173.) / 6173., 341. / 6173., -1552. / 6173., 968. / 6173,
                    4227. / 6173., -520. / 6173., 3833. / 6173., -1277 / 6173.,
                    873. / 6173., 265. / 6173., -1894. / 6173., 354. / 6173.,
                    480. / 6173., -24. / 6173., -108. / 6173., 131. / 6173.};
    auto a = I1.inverse();
    EXPECT_EQ(a, expected);
}

TEST(matrix_test, translation)
{
    vec4 v{1, 1, 1, 1};
    mat4x4 t_mat{mat4x4::get_translation_matrix({2, 2, 2})};
    vec4 expected{3, 3, 3, 1};
    EXPECT_EQ(translate_vec(t_mat, v), expected);
}

TEST(matrix_test, get_rotation_matrix)
{
    mat4x4 expected{
        std::sqrt(2.f) / 2, -std::sqrt(2.f) / 2, 0, 0,
        std::sqrt(2.f) / 2, std::sqrt(2.f) / 2, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};

    EXPECT_EQ(mat4x4::get_rotation_matrix(vec3{0, 0, 45}), expected);
}