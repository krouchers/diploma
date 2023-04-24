#include <cmath>
#include <numbers>

#include "math/common.hpp"
#include "math/transforms.hpp"
#include "math/mat4x4.hpp"
#include "math/vec4.hpp"

namespace math
{
    Mat4x4 Perspective(float n, float f, float fov, float aspect_ratio)
    {
        float focal_length{1.f / std::tan(Radians(fov) / 2.f)};
        float r = n / focal_length;
        float l = -r;
        float t = aspect_ratio * n / focal_length;
        float b = -t;
        return math::Mat4x4{{{2.0f * n / (r - l), 0, (r + l) / (r - l), 0},
                             {0, 2.0f * n / (t - b), (t + b) / (t - b), 0},
                             {0, 0, -(f + n) / (f - n), -2.0f * n * f / (f - n)},
                             {0, 0, -1, 0}}};
    }

    constexpr Mat4x4 Translate(const Vec4 &v) noexcept
    {
        return Mat4x4{{{1, 0, 0, v[0]},
                       {0, 1, 0, v[1]},
                       {0, 0, 1, v[2]},
                       {0, 0, 0, 1}}};
    }

    constexpr Mat4x4 RotationAroundAxis(Vec3 axis, float angle) noexcept
    {
        float c = std::cos(angle);
        float s = std::sin(angle);

        float x{axis[0]};
        float y{axis[1]};
        float z{axis[2]};

        return Mat4x4{{{c + (1 - c) * x * x, (1 - c) * x * y - s * z, (1 - c) * x * z + s * y, 0.f},
                       {(1 - c) * x * y + s * z, c + (1 - c) * y * y, (1 - c) * y * z - s * x, 0.f},
                       {(1 - c) * x * z - s * y, (1 - c) * y * z + s * x, c + (1 - c) * z * z, 0.f},
                       {0.f, 0.f, 0.f, 0.f}}};
    }

}