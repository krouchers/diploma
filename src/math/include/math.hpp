#pragma once

#include <stdexcept>
#include <cmath>
#include <numbers>

constexpr inline float radians(float degrees)
{
    return degrees * std::numbers::pi / 180.f;
}

struct vec4
{

    constexpr vec4()
        : x_{0}, y_{0}, z_{0}, w_{0} {};
    constexpr vec4(float x, float y, float z, float w)
        : x_{x}, y_{y}, z_{z}, w_{w} {};

    constexpr float &operator[](int i)
    {
        if (!(i >= 0 && i <= 3))
        {
            throw std::out_of_range("Out of range indexing in vec4");
        }
        return data[i];
    }

     constexpr float operator[](int i) const
    {
        if (!(i >= 0 && i <= 3))
        {
            throw std::out_of_range("Out of range indexing in vec4");
        }
        return data[i];
    }

    constexpr bool operator==(const vec4 &rhs) const
    {
        return x_ == rhs.x_ &&
               y_ == rhs.y_ &&
               z_ == rhs.z_ &&
               w_ == rhs.w_;
    }

    constexpr bool operator!=(const vec4 &rhs) const
    {
        return !(*this == rhs);
    }

    constexpr vec4 &operator*=(const float k)
    {
        for (auto &elem : data)
            elem *= k;

        return *this;
    }

    float *begin()
    {
        return data;
    }

    float *end()
    {
        return data + sizeof(data) / sizeof(data[0]);
    }

    union
    {
        struct
        {
            float x_, y_, z_, w_;
        };

        float data[4];
    };
};

constexpr vec4 operator*(const float k, const vec4 &rhs)
{
    vec4 res{};
    for (int i{0}; i < 4; ++i)
        res[i] = k * rhs[i];

    return res;
}

constexpr vec4 operator*(const vec4 &rhs, const float k)
{
    vec4 res{};
    for (int i{0}; i < 4; ++i)
        res[i] = k * rhs[i];

    return res;
}

constexpr vec4 operator/(const vec4 &rhs, const float k)
{
    vec4 res{};
    for (int i{0}; i < 4; ++i)
        res[i] = rhs[i] / k;

    return res;
}

struct vec3
{
    float x, y, z;
};

struct vec2
{
    float x, y;
};

struct mat4x4
{
    static const mat4x4 I;
    constexpr mat4x4()
    {
        *this = I;
    }

    constexpr mat4x4(
        std::initializer_list<vec4> il)
    {
        for (std::size_t i = 0; i < il.size(); ++i)
        {
            rows[i] = *(il.begin() + i);
        }
    }

    constexpr mat4x4(
        std::initializer_list<float> il)
    {
        for (std::size_t i = 0; i < 4; ++i)
            for (std::size_t j = 0; j < 4; ++j)
            {
                rows[i][j] = *(il.begin() + 4 * i + j);
            }
    }

    constexpr bool operator==(const mat4x4 &rhs) const
    {
        for (std::size_t i = 0; i < 16; ++i)
            if (std::abs(data[i] - rhs.data[i]) > eps)
                return false;
        return true;
    }

    constexpr vec4 &operator[](std::size_t index)
    {
        return rows[index];
    }

    constexpr vec4 operator[](std::size_t index) const
    {
        return rows[index];
    }

    constexpr vec4 *begin()
    {
        return rows;
    }

    constexpr vec4 *end()
    {
        return rows + sizeof(rows) / sizeof(rows[0]);
    }

    constexpr mat4x4 inverse();

    static mat4x4 get_rotation_matrix(vec3 euler_angles);
    static mat4x4 get_projection_matrix(float n, float f, float fov, float aspect_ratio);

    constexpr static mat4x4 get_translation_matrix(const vec3 &translate);

    constexpr mat4x4 transpose()
    {
        mat4x4 res{};
        for (int i{0}; i < 4; ++i)
            for (int j{0}; j < 4; ++j)
            {
                res[j][i] = (*this)[i][j];
            }
        return res;
    }

    union
    {
        vec4 rows[4]{};
        float data[16];
    };

    static inline constexpr float eps{1e-7};
};

constexpr mat4x4 operator*(const mat4x4 &lhs, const float k)
{
    mat4x4 res{lhs};
    for (vec4 &row : res)
    {
        row *= k;
    }

    return res;
}

constexpr mat4x4 operator*(const float k, const mat4x4 &rhs)
{
    mat4x4 res{rhs};
    for (vec4 &row : res)
    {
        row = row * k;
    }

    return res;
}

constexpr mat4x4 operator*(const mat4x4 &lhs, const mat4x4 &rhs)
{
    return mat4x4{
        rhs[0][0] * lhs[0][0] + rhs[1][0] * lhs[0][1] + rhs[2][0] * lhs[0][2] + rhs[3][0] * lhs[0][3],
        rhs[0][0] * lhs[1][0] + rhs[1][0] * lhs[1][1] + rhs[2][0] * lhs[1][2] + rhs[3][0] * lhs[1][3],
        rhs[0][0] * lhs[2][0] + rhs[1][0] * lhs[2][1] + rhs[2][0] * lhs[2][2] + rhs[3][0] * lhs[2][3],
        rhs[0][0] * lhs[3][0] + rhs[1][0] * lhs[3][1] + rhs[2][0] * lhs[3][2] + rhs[3][0] * lhs[3][3],
        rhs[0][1] * lhs[0][0] + rhs[1][1] * lhs[0][1] + rhs[2][1] * lhs[0][2] + rhs[3][1] * lhs[0][3],
        rhs[0][1] * lhs[1][0] + rhs[1][1] * lhs[1][1] + rhs[2][1] * lhs[1][2] + rhs[3][1] * lhs[1][3],
        rhs[0][1] * lhs[2][0] + rhs[1][1] * lhs[2][1] + rhs[2][1] * lhs[2][2] + rhs[3][1] * lhs[2][3],
        rhs[0][1] * lhs[3][0] + rhs[1][1] * lhs[3][1] + rhs[2][1] * lhs[3][2] + rhs[3][1] * lhs[3][3],
        rhs[0][2] * lhs[0][0] + rhs[1][2] * lhs[0][1] + rhs[2][2] * lhs[0][2] + rhs[3][2] * lhs[0][3],
        rhs[0][2] * lhs[1][0] + rhs[1][2] * lhs[1][1] + rhs[2][2] * lhs[1][2] + rhs[3][2] * lhs[1][3],
        rhs[0][2] * lhs[2][0] + rhs[1][2] * lhs[2][1] + rhs[2][2] * lhs[2][2] + rhs[3][2] * lhs[2][3],
        rhs[0][2] * lhs[3][0] + rhs[1][2] * lhs[3][1] + rhs[2][2] * lhs[3][2] + rhs[3][2] * lhs[3][3],
        rhs[0][3] * lhs[0][0] + rhs[1][3] * lhs[0][1] + rhs[2][3] * lhs[0][2] + rhs[3][3] * lhs[0][3],
        rhs[0][3] * lhs[1][0] + rhs[1][3] * lhs[1][1] + rhs[2][3] * lhs[1][2] + rhs[3][3] * lhs[1][3],
        rhs[0][3] * lhs[2][0] + rhs[1][3] * lhs[2][1] + rhs[2][3] * lhs[2][2] + rhs[3][3] * lhs[2][3],
        rhs[0][3] * lhs[3][0] + rhs[1][3] * lhs[3][1] + rhs[2][3] * lhs[3][2] + rhs[3][3] * lhs[3][3]};
}

inline mat4x4 mat4x4::get_projection_matrix(float n, float f, float fov, float aspect_ratio)
{
    float focal_length{1.f / std::tan(radians(fov))};
    float r = n / focal_length;
    float l = -r;
    float t = aspect_ratio * n / focal_length;
    float b = -t;
    return mat4x4{
        vec4{2.0f * n / (r - l), 0, (r + l) / (r - l), 0},
        vec4{0, 2.0f * n / (t - b), (t + b) / (t - b), 0},
        vec4{0, 0, -(f + n) / (f - n), -2.0f * n * f / (f - n)},
        vec4{0, 0, -1, 0},
    };
}

constexpr mat4x4 project(float n, float f, float l, float r, float b, float t)
{
    return mat4x4{
        vec4{-2.0f * n / (r - l), 0, -(r + l) / (r - l), 0},
        vec4{0, -2.0f / (t - b), -(t + b) / (t - b), 0},
        vec4{0, 0, (f + n) / (f - b), 2.0f * n * f / (f - n)},
        vec4{0, 0, 1, 0},
    };
}

constexpr mat4x4 translate(const vec4 &v)
{
    return mat4x4{
        vec4{1, 0, 0, v.x_},
        vec4{0, 1, 0, v.y_},
        vec4{0, 0, 1, v.z_},
        vec4{0, 0, 0, 1},
    };
}

constexpr inline mat4x4 mat4x4::I = {
    vec4{1, 0, 0, 0},
    vec4{0, 1, 0, 0},
    vec4{0, 0, 1, 0},
    vec4{0, 0, 0, 1},
};

constexpr mat4x4 mat4x4::inverse()
{
    float a11{(*this)[0][0]};
    float a12{(*this)[0][1]};
    float a13{(*this)[0][2]};
    float a14{(*this)[0][3]};

    float a21{(*this)[1][0]};
    float a22{(*this)[1][1]};
    float a23{(*this)[1][2]};
    float a24{(*this)[1][3]};

    float a31{(*this)[2][0]};
    float a32{(*this)[2][1]};
    float a33{(*this)[2][2]};
    float a34{(*this)[2][3]};

    float a41{(*this)[3][0]};
    float a42{(*this)[3][1]};
    float a43{(*this)[3][2]};
    float a44{(*this)[3][3]};

    float det11{a22 * (a33 * a44 - a34 * a43) + a23 * (a34 * a42 - a32 * a44) + a24 * (a32 * a43 - a33 * a42)};
    float det12{a21 * (a33 * a44 - a34 * a43) + a23 * (a34 * a41 - a31 * a44) + a24 * (a31 * a43 - a33 * a41)};
    float det13{a21 * (a32 * a44 - a34 * a42) + a22 * (a34 * a41 - a31 * a44) + a24 * (a31 * a42 - a32 * a41)};
    float det14{a21 * (a32 * a43 - a33 * a42) + a22 * (a33 * a41 - a31 * a43) + a23 * (a31 * a42 - a32 * a41)};

    float k{1.f / (a11 * det11 - a12 * det12 + a13 * det13 - a14 * det14)};
    [[maybe_unused]] float det{(a11 * det11 - a12 * det12 + a13 * det13 - a14 * det14)};

    return k * mat4x4{
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
                   a11 * (a22 * a33 - a23 * a32) + a12 * (a23 * a31 - a21 * a33) + a13 * (a21 * a32 - a22 * a31),
               }
                   .transpose();
}

inline mat4x4 mat4x4::get_rotation_matrix(vec3 euler_angles)
{
    auto x_rad{radians(euler_angles.x)};
    auto y_rad{radians(euler_angles.y)};
    auto z_rad{radians(euler_angles.z)};

    mat4x4 rot_around_x{
        {1, 0, 0, 0},
        {0, std::cos(x_rad), -std::sin(x_rad), 0},
        {0, std::sin(x_rad), std::cos(x_rad), 0},
        {0, 0, 0, 1}};

    mat4x4 rot_around_y{
        {std::cos(y_rad), 0, std::sin(y_rad), 0},
        {0, 1, 0, 0},
        {-std::sin(y_rad), 0, std::cos(y_rad), 0},
        {0, 0, 0, 1}};

    mat4x4 rot_around_z{
        {std::cos(z_rad), -std::sin(z_rad), 0, 0},
        {std::sin(z_rad), std::cos(z_rad), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};

    return rot_around_z * rot_around_y * rot_around_x;
}

inline constexpr mat4x4 mat4x4::get_translation_matrix(const vec3 &translate)
{
    mat4x4 res{};
    res[0][3] = translate.x;
    res[1][3] = translate.y;
    res[2][3] = translate.z;

    return res;
}

inline constexpr vec4 operator*(const mat4x4 &rot, const vec4 &vec)
{
    return vec4{
        rot[0][0] * vec[0] + rot[0][1] * vec[1] + rot[0][2] * vec[2] + rot[0][3] * vec[3],
        rot[1][0] * vec[0] + rot[1][1] * vec[1] + rot[1][2] * vec[2] + rot[1][3] * vec[3],
        rot[2][0] * vec[0] + rot[2][1] * vec[1] + rot[2][2] * vec[2] + rot[2][3] * vec[3],
        rot[3][0] * vec[0] + rot[3][1] * vec[1] + rot[3][2] * vec[2] + rot[3][3] * vec[3],
    };
}

inline constexpr vec4 rotate_vec(const mat4x4 &rot, const vec4 &vec4)
{
    return rot * vec4;
}

inline constexpr vec4 translate_vec(const mat4x4 &translation_mat, const vec4 &vec4)
{
    return translation_mat * vec4;
}
