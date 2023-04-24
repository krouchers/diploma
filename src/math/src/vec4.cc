#include "math/vec4.hpp"

namespace math
{
    template struct Vec<4>;

    template Vec4 operator*(const float k, const Vec4 &rhs);
    template Vec4 operator*(const Vec4 &rhs, const float k);
    template Vec4 operator/(const float k, const Vec4 &rhs);
    template Vec4 operator/(const Vec4 &rhs, const float k);
}