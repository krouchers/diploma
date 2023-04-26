#pragma once

namespace math
{
    static const float kEps = 1e-5;

    constexpr float Radians(float degrees) noexcept
    {
        return degrees * 3.1415926535f / 180.f;
    }
}