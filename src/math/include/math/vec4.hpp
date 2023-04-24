#pragma once
#include "math/vec.hpp"

namespace math
{
    using Vec4 = Vec<4>;
    extern template struct math::Vec<4>;
    extern template Vec4 operator*(const float k, const Vec4 &rhs);
    extern template Vec4 operator*(const Vec4 &rhs, const float k);
    extern template Vec4 operator/(const Vec4 &rhs, const float k);
    extern template Vec4 operator/(const float k, const Vec4 &rhs);
}