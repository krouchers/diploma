#include "math/vec2.hpp"

namespace math
{
    template struct Vec<2>;

    template Vec2 operator*(const float k, const Vec2 &rhs);
    template Vec2 operator*(const Vec2 &rhs, const float k);
    template Vec2 operator/(const float k, const Vec2 &rhs);
    template Vec2 operator/(const Vec2 &rhs, const float k);
}