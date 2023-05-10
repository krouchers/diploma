#pragma once
#include <numbers>

namespace math
{
    static const float kEps = 1e-5;

    constexpr float Radians(float degrees) noexcept
    {
        return degrees * 3.1415926535f / 180.f;
    }

    constexpr float Degrees(float radians) noexcept
    {
        return radians * 180.0f / std::numbers::pi;
    }

    constexpr float Sign(float number)
    {
        return number > 0.0f ? 1.0f : number < 0.0f ? -1.0f
                                                    : 0.0;
    }
}