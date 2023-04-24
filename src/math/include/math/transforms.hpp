#pragma once
#include "math/mat4x4.hpp"
#include "math/vec3.hpp"

namespace math
{
    Mat4x4 Perspective(float n, float f, float fov, float aspect_ratio);
    constexpr Mat4x4 Translate(const Vec3 &translate) noexcept;
    constexpr Mat4x4 RotationAroundAxis(Vec3 axis, float angle) noexcept;
}
