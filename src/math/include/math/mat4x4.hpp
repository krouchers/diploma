#pragma once
#include <algorithm>
#include "math/vec4.hpp"

namespace math
{
    struct Mat4x4
    {
    public:
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

        float data[4][4];
    };

    constexpr Vec4 operator*(const Mat4x4 &rot, const Vec4 &vec) noexcept;

    Mat4x4 operator*(float k, const Mat4x4 &lhs);

    Mat4x4 GetProjection(float n, float f, float fov, float aspect_ratio);
}