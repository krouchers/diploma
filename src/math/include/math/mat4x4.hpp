#pragma once
#include <algorithm>
#include "math/vec4.hpp"

namespace math
{
    struct Mat4x4
    {
        constexpr Mat4x4() : data{0}
        {
        }
        constexpr Mat4x4(float n) : Mat4x4()
        {
            for (size_t i{0}; i < 4; ++i)
            {
                data[i][i] = n;
            }
        }
        constexpr Mat4x4(std::initializer_list<float> il)
        {
            std::copy(il.begin(), il.begin() + 16, &data[0][0]);
        }
        const float *operator[](size_t index) const
        {
            return data[index];
        }

        float *operator[](size_t index)
        {
            return data[index];
        }

        bool operator==(Mat4x4 const &rhs) const;

        Mat4x4 operator*(const Mat4x4 &rhs);

        Mat4x4 Transpose();

        Mat4x4 Inverse();

        float data[4][4]{0};
    };

    constexpr Vec4 operator*(const Mat4x4 &m, const Vec4 &v) noexcept
    {

        Vec4 res{};
        for (size_t i{0}; i < 4; ++i)
        {
            for (size_t j{0}; j < 4; ++j)
                res[i] += m[i][j] * v[j];
        }
        return res;
    }

    Mat4x4 operator*(float k, const Mat4x4 &lhs);

    Mat4x4 GetProjection(float n, float f, float fov, float aspect_ratio);
}