#pragma once
#include "math/vec.hpp"

namespace math
{
    using Vec3 = Vec<3>;
    extern template struct Vec<3>;
    extern template Vec3 operator*(const float k, const Vec3 &rhs);
    extern template Vec3 operator*(const Vec3 &rhs, const float k);
    extern template Vec3 operator/(const Vec3 &rhs, const float k);
    extern template Vec3 operator/(const float k, const Vec3 &rhs);
}
