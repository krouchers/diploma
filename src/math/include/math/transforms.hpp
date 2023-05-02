#pragma once
#include "math/mat4x4.hpp"
#include "math/vec3.hpp"

namespace math
{
    Mat4x4 Perspective(float n, float f, float fov, float aspect_ratio);
    constexpr Mat4x4 Translate(const Vec4 &v) noexcept
    {
        return Mat4x4{1, 0, 0, v[0],
                      0, 1, 0, v[1],
                      0, 0, 1, v[2],
                      0, 0, 0, 1};
    }
    constexpr Mat4x4 RotationAroundAxis(Vec3 axis, float angle) noexcept;
}
