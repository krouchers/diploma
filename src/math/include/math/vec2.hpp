#pragma once
#include "math/vec.hpp"

namespace math
{
    using Vec2 = Vec<2>;
    extern template struct Vec<2>;
    extern template Vec2 operator*(const float k, const Vec2 &rhs);
    extern template Vec2 operator*(const Vec2 &rhs, const float k);
    extern template Vec2 operator/(const Vec2 &rhs, const float k);
    extern template Vec2 operator/(const float k, const Vec2 &rhs);
}