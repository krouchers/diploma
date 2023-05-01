#include <cmath>
#include <numbers>

#include "math/mat4x4.hpp"
#include "math/common.hpp"

namespace math
{
    Mat4x4 Mat4x4::Inverse()
    {
        auto m{*this};
        float a11{m[0][0]};
        float a12{m[0][1]};
        float a13{m[0][2]};
        float a14{m[0][3]};

        float a21{m[1][0]};
        float a22{m[1][1]};
        float a23{m[1][2]};
        float a24{m[1][3]};

        float a31{m[2][0]};
        float a32{m[2][1]};
        float a33{m[2][2]};
        float a34{m[2][3]};

        float a41{m[3][0]};
        float a42{m[3][1]};
        float a43{m[3][2]};
        float a44{m[3][3]};

        float det11{a22 * (a33 * a44 - a34 * a43) + a23 * (a34 * a42 - a32 * a44) + a24 * (a32 * a43 - a33 * a42)};
        float det12{a21 * (a33 * a44 - a34 * a43) + a23 * (a34 * a41 - a31 * a44) + a24 * (a31 * a43 - a33 * a41)};
        float det13{a21 * (a32 * a44 - a34 * a42) + a22 * (a34 * a41 - a31 * a44) + a24 * (a31 * a42 - a32 * a41)};
        float det14{a21 * (a32 * a43 - a33 * a42) + a22 * (a33 * a41 - a31 * a43) + a23 * (a31 * a42 - a32 * a41)};

        float k{1.f / (a11 * det11 - a12 * det12 + a13 * det13 - a14 * det14)};

        return k * Mat4x4{
                       det11,
                       -det12,
                       det13,
                       -det14,

                       -(a12 * (a33 * a44 - a34 * a43) + a13 * (a34 * a42 - a32 * a44) + a14 * (a32 * a43 - a33 * a42)),
                       a11 * (a33 * a44 - a34 * a43) + a13 * (a34 * a41 - a31 * a44) + a14 * (a31 * a43 - a33 * a41),
                       -(a11 * (a32 * a44 - a34 * a42) + a12 * (a34 * a41 - a31 * a44) + a14 * (a31 * a42 - a32 * a41)),
                       a11 * (a32 * a43 - a33 * a41) + a12 * (a33 * a41 - a31 * a43) + a13 * (a31 * a42 - a32 * a41),

                       a12 * (a23 * a44 - a24 * a42) + a13 * (a24 * a42 - a22 * a44) + a14 * (a22 * a43 - a23 * a42),
                       -(a11 * (a23 * a44 - a24 * a43) + a13 * (a24 * a41 - a21 * a44) + a14 * (a21 * a43 - a23 * a41)),
                       a11 * (a22 * a44 - a24 * a42) + a12 * (a24 * a41 - a21 * a44) + a14 * (a21 * a42 - a22 * a41),
                       -(a11 * (a22 * a43 - a23 * a42) + a12 * (a23 * a41 - a21 * a43) + a13 * (a21 * a42 - a22 * a41)),

                       -(a12 * (a23 * a34 - a24 * a33) + a13 * (a24 * a32 - a22 * a34) + a14 * (a22 * a33 - a23 * a32)),
                       a11 * (a23 * a34 - a24 * a33) + a13 * (a24 * a31 - a21 * a34) + a14 * (a21 * a33 - a23 * a31),
                       -(a11 * (a22 * a34 - a24 * a32) + a12 * (a24 * a31 - a21 * a33) + a14 * (a21 * a32 - a22 * a31)),
                       a11 * (a22 * a33 - a23 * a32) + a12 * (a23 * a31 - a21 * a33) + a13 * (a21 * a32 - a22 * a31)}
                       .Transpose();
    }

    Mat4x4 Mat4x4::Transpose()
    {
        Mat4x4 m{*this};
        Mat4x4 res;
        for (size_t i{0}; i < 4; ++i)
            for (size_t j{0}; j < 4; ++j)
                std::swap(m[i][j], res[j][i]);
        return res;
    }

    Mat4x4 Mat4x4::operator*(const Mat4x4 &rhs)
    {
        const Mat4x4 &lhs = *this;
        Mat4x4 res;
        for (size_t i{0}; i < 4; ++i)
            for (size_t j{0}; j < 4; ++j)
                for (size_t k{0}; k < 4; ++k)
                    res[i][j] += lhs[i][k] * rhs[k][j];
        return res;
    }

    Mat4x4 operator*(float k, const Mat4x4 &lhs)
    {
        Mat4x4 res{};
        for (size_t i{0}; i < 4; ++i)
            for (size_t j{0}; j < 4; ++j)
                res[i][j] = lhs[i][j] * k;
        return res;
    }

    bool Mat4x4::operator==(Mat4x4 const &rhs) const
    {
        for (size_t i{0}; i < 4; ++i)
            for (size_t j{0}; j < 4; ++j)
                if (std::abs(data[i][j] - rhs[i][j]) > kEps)
                    return false;
        return true;
    }
}