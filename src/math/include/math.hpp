#pragma once

#include <stdexcept>
#include <cmath>
#include <numbers>

struct Vec2;
struct Vec3;
struct Vec4;
struct Mat3x3;
struct Mat4x4;

constexpr Vec4 operator*(const float k, const Vec4 &rhs);
constexpr Vec4 operator*(const Vec4 &rhs, const float k);
constexpr Vec4 operator/(const Vec4 &rhs, const float k);

constexpr Vec3 operator*(const Mat3x3 &m, const Vec3 &v);
constexpr Vec3 operator==(const Mat3x3 &m, const Vec3 &v);

constexpr Mat3x3 operator*(const Mat3x3 &lhs, const Mat3x3 &rhs);

static inline constexpr float kEps{1e-4};

constexpr inline float Radians(float degrees)
{
    return degrees * std::numbers::pi / 180.f;
}

struct Vec4
{

    constexpr Vec4()
        : x_{0}, y_{0}, z_{0}, w_{0} {};
    constexpr Vec4(float x, float y, float z, float w)
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

    constexpr bool operator==(const Vec4 &rhs) const
    {
        return std::abs(x_ - rhs.x_) < kEps &&
               std::abs(y_ - rhs.y_) < kEps &&
               std::abs(z_ - rhs.z_) < kEps &&
               std::abs(w_ - rhs.w_) < kEps;
    }

    constexpr bool operator!=(const Vec4 &rhs) const
    {
        return !(*this == rhs);
    }

    constexpr Vec4 &operator*=(const float k)
    {
        for (auto &elem : data)
        {
            elem *= k;
        }

        return *this;
    }

    float *Begin()
    {
        return data;
    }

    float *End()
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

constexpr Vec4 operator*(const float k, const Vec4 &rhs)
{
    Vec4 res{};
    for (int i{0}; i < 4; ++i)
        res[i] = k * rhs[i];

    return res;
}

constexpr Vec4 operator*(const Vec4 &rhs, const float k)
{
    Vec4 res{};
    for (int i{0}; i < 4; ++i)
        res[i] = k * rhs[i];

    return res;
}

constexpr Vec4 operator/(const Vec4 &rhs, const float k)
{
    return rhs * (1.f / k);
}

struct Mat3x3
{
    float data[3][3];
    Vec3 &operator[](int i)
    {
        return (*reinterpret_cast<Vec3 *>(data[i]));
    }

    const Vec3 &operator[](int i) const
    {
        return (*reinterpret_cast<const Vec3 *>(data[i]));
    }

    bool operator==(const Mat3x3 &rhs) const
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                if ((data[i][j] - rhs.data[i][j]) > kEps)
                {
                    return false;
                }
            }
        return true;
    }

    inline operator Mat4x4();

    static Mat3x3 GetRotationMatrix(Vec3 euler_angles);
    inline static Mat3x3 GetRotationAroundAxis(Vec3 axis, float angle);
};

struct Vec3
{
    constexpr Vec3() {}
    constexpr Vec3(float x, float y, float z) : x_{x}, y_{y}, z_{z} {}
    union
    {
        struct
        {
            float x_, y_, z_;
        };
        float data[3];
    };

    float operator[](int i)
    {
        return data[i];
    }

    float operator[](int i) const
    {
        return data[i];
    }

    Vec3 &operator*(float k)
    {
        for (int i = 0; i < 3; ++i)
        {
            data[i] *= k;
        }
        return *this;
    }
};

constexpr Vec3 operator*(const Mat3x3 &m, const Vec3 &v)
{
    Vec3 res{};
    res.x_ = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2];
    res.y_ = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2];
    res.z_ = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2];
    return res;
}

struct Vec2
{
    float x, y;
};

struct Mat4x4
{
    static const Mat4x4 kI;
    constexpr Mat4x4()
    {
        *this = kI;
    }

    constexpr Mat4x4(
        std::initializer_list<Vec4> il)
    {
        for (std::size_t i = 0; i < il.size(); ++i)
        {
            rows[i] = *(il.begin() + i);
        }
    }

    constexpr Mat4x4(
        std::initializer_list<float> il)
    {
        for (std::size_t i = 0; i < 4; ++i)
            for (std::size_t j = 0; j < 4; ++j)
            {
                rows[i][j] = *(il.begin() + 4 * i + j);
            }
    }

    constexpr bool operator==(const Mat4x4 &rhs) const
    {
        for (std::size_t i = 0; i < 16; ++i)
            if (std::abs(data[i] - rhs.data[i]) > kEps)
                return false;
        return true;
    }

    constexpr Vec4 &operator[](std::size_t index)
    {
        return rows[index];
    }

    constexpr Vec4 operator[](std::size_t index) const
    {
        return rows[index];
    }

    constexpr Vec4 *begin()
    {
        return rows;
    }

    constexpr Vec4 *end()
    {
        return rows + sizeof(rows) / sizeof(rows[0]);
    }

    constexpr Mat4x4 Inverse();

    static Mat4x4 GetRotationMatrix(Vec3 euler_angles);
    static Mat4x4 GetProjectionMatrix(float n, float f, float fov, float aspect_ratio);

    constexpr static Mat4x4 GetTranslationMatrix(const Vec3 &translate);

    constexpr Mat4x4 Transpose()
    {
        Mat4x4 res{};
        for (int i{0}; i < 4; ++i)
            for (int j{0}; j < 4; ++j)
            {
                res[j][i] = (*this)[i][j];
            }
        return res;
    }

    union
    {
        Vec4 rows[4]{};
        float data[16];
    };
};

constexpr Mat4x4 operator*(const Mat4x4 &lhs, const float k)
{
    Mat4x4 res{lhs};
    for (Vec4 &row : res)
    {
        row *= k;
    }

    return res;
}

constexpr Mat4x4 operator*(const float k, const Mat4x4 &rhs)
{
    Mat4x4 res{rhs};
    for (Vec4 &row : res)
    {
        row = row * k;
    }

    return res;
}

constexpr Mat4x4 operator*(const Mat4x4 &lhs, const Mat4x4 &rhs)
{
    return Mat4x4{
        lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0],
        lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1],
        lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2],
        lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3] + lhs[0][3] * rhs[3][3],

        lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0],
        lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1],
        lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2],
        lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3] + lhs[1][3] * rhs[3][3],

        lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0],
        lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1],
        lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2] + lhs[2][3] * rhs[3][2],
        lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3] + lhs[2][2] * rhs[2][3] + lhs[2][3] * rhs[3][3],

        lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0] + lhs[3][3] * rhs[3][0],
        lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1] + lhs[3][3] * rhs[3][1],
        lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2] + lhs[3][2] * rhs[2][2] + lhs[3][3] * rhs[3][2],
        lhs[3][0] * rhs[0][3] + lhs[3][1] * rhs[1][3] + lhs[3][2] * rhs[2][3] + lhs[3][3] * rhs[3][3]};
}

inline Mat4x4 Mat4x4::GetProjectionMatrix(float n, float f, float fov, float aspect_ratio)
{
    float focal_length{1.f / std::tan(Radians(fov))};
    float r = n / focal_length;
    float l = -r;
    float t = aspect_ratio * n / focal_length;
    float b = -t;
    return Mat4x4{
        Vec4{2.0f * n / (r - l), 0, (r + l) / (r - l), 0},
        Vec4{0, 2.0f * n / (t - b), (t + b) / (t - b), 0},
        Vec4{0, 0, -(f + n) / (f - n), -2.0f * n * f / (f - n)},
        Vec4{0, 0, -1, 0},
    };
}

constexpr Mat4x4 Project(float n, float f, float l, float r, float b, float t)
{
    return Mat4x4{
        Vec4{-2.0f * n / (r - l), 0, -(r + l) / (r - l), 0},
        Vec4{0, -2.0f / (t - b), -(t + b) / (t - b), 0},
        Vec4{0, 0, (f + n) / (f - b), 2.0f * n * f / (f - n)},
        Vec4{0, 0, 1, 0},
    };
}

constexpr Mat4x4 Translate(const Vec4 &v)
{
    return Mat4x4{
        Vec4{1, 0, 0, v.x_},
        Vec4{0, 1, 0, v.y_},
        Vec4{0, 0, 1, v.z_},
        Vec4{0, 0, 0, 1},
    };
}

constexpr inline Mat4x4 Mat4x4::kI = {
    Vec4{1, 0, 0, 0},
    Vec4{0, 1, 0, 0},
    Vec4{0, 0, 1, 0},
    Vec4{0, 0, 0, 1},
};

constexpr Mat4x4 Mat4x4::Inverse()
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
    [[maybe_unused]] float det{(a11 * det11 - a12 * det12 + a13 * det13 - a14 * det14)};

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
                   a11 * (a22 * a33 - a23 * a32) + a12 * (a23 * a31 - a21 * a33) + a13 * (a21 * a32 - a22 * a31),
               }
                   .Transpose();
}

inline constexpr Mat4x4 Mat4x4::GetTranslationMatrix(const Vec3 &translate)
{
    Mat4x4 res{};
    res[0][3] = translate.x_;
    res[1][3] = translate.y_;
    res[2][3] = translate.z_;

    return res;
}

Mat3x3 Mat3x3::GetRotationAroundAxis(Vec3 axis, float angle)
{
    float c = std::cos(angle);
    float s = std::sin(angle);

    return Mat3x3{{{c + (1 - c) * axis.x_ * axis.x_, (1 - c) * axis.x_ * axis.y_ - s * axis.z_, (1 - c) * axis.x_ * axis.z_ + s * axis.y_},
                   {(1 - c) * axis.x_ * axis.y_ + s * axis.z_, c + (1 - c) * axis.y_ * axis.y_, (1 - c) * axis.y_ * axis.z_ - s * axis.x_},
                   {(1 - c) * axis.x_ * axis.z_ - s * axis.y_, (1 - c) * axis.y_ * axis.z_ + s * axis.x_, c + (1 - c) * axis.z_ * axis.z_}}};
}

inline constexpr Vec4 operator*(const Mat4x4 &rot, const Vec4 &vec)
{
    return Vec4{
        rot[0][0] * vec[0] + rot[0][1] * vec[1] + rot[0][2] * vec[2] + rot[0][3] * vec[3],
        rot[1][0] * vec[0] + rot[1][1] * vec[1] + rot[1][2] * vec[2] + rot[1][3] * vec[3],
        rot[2][0] * vec[0] + rot[2][1] * vec[1] + rot[2][2] * vec[2] + rot[2][3] * vec[3],
        rot[3][0] * vec[0] + rot[3][1] * vec[1] + rot[3][2] * vec[2] + rot[3][3] * vec[3],
    };
}

inline constexpr Vec3 RotateVec(const Mat3x3 &rot, const Vec3 &v)
{
    return rot * v;
}

inline constexpr Vec4 TranslateVec(const Mat4x4 &translation_mat, const Vec4 &vec4)
{
    return translation_mat * vec4;
}

constexpr bool operator==(const Vec3 &lhs, const Vec3 &rhs)
{
    for (int i = 0; i < 3; ++i)
    {
        if (!(lhs[i] - rhs[i] < kEps))
            return false;
    }
    return true;
}

inline Mat3x3 Mat3x3::GetRotationMatrix(Vec3 euler_angles)
{
    auto x_rad{Radians(euler_angles.x_)};
    auto y_rad{Radians(euler_angles.y_)};
    auto z_rad{Radians(euler_angles.z_)};

    Mat3x3 rot_around_x{
        {{1, 0, 0},
         {0, std::cos(x_rad), -std::sin(x_rad)},
         {0, std::sin(x_rad), std::cos(x_rad)}}};

    Mat3x3 rot_around_y{
        {{std::cos(y_rad), 0, std::sin(y_rad)},
         {0, 1, 0},
         {-std::sin(y_rad), 0, std::cos(y_rad)}}};

    Mat3x3 rot_around_z{
        {{std::cos(z_rad), -std::sin(z_rad), 0},
         {std::sin(z_rad), std::cos(z_rad), 0},
         {0, 0, 1}}};

    return rot_around_z * rot_around_y * rot_around_x;
}

constexpr Mat3x3 operator*(const Mat3x3 &lhs, const Mat3x3 &rhs)
{
    return Mat3x3{{
        {lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0],
         lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1],
         lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2]},

        {lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0],
         lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1],
         lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2]},

        {lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0],
         lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1],
         lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2]},
    }};
}

Mat3x3::operator Mat4x4()
{
    return Mat4x4{
        data[0][0], data[0][1], data[0][2], 0,
        data[1][0], data[1][1], data[1][2], 0,
        data[2][0], data[2][1], data[2][2], 0,
        0, 0, 0, 1};
}