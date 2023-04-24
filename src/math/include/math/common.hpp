#pragma once
#include <numbers>

namespace math
{
    static const float kEps = 1e-5;

    constexpr float Radians(float degrees) noexcept
    {
        return degrees * std::numbers::pi / 180.f;
    }
}