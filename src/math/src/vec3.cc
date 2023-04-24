#include "math/vec3.hpp"

namespace math
{
    template struct Vec<3>;

    template Vec3 operator*(const float k, const Vec3 &rhs);
    template Vec3 operator*(const Vec3 &rhs, const float k);
    template Vec3 operator/(const float k, const Vec3 &rhs);
    template Vec3 operator/(const Vec3 &rhs, const float k);
}