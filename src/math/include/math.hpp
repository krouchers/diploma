#include <stdexcept>
#include <cmath>
#include <numbers>

constexpr float radians(float degrees)
{
    return degrees * std::numbers::pi / 180.f;
}

struct vec4
{

    constexpr vec4()
        : x_{0}, y_{0}, z_{0}, w_{0} {};
    constexpr vec4(float x, float y, float z, float w)
        : x_{x}, y_{y}, z_{z}, w_{w} {};

    float &operator[](int i)
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
        for (std::size_t i = 0; i < 4; ++i)
            if (rows[i] != rhs.rows[i])
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

    const vec4 *begin() const
    {
        return rows;
    }

    const vec4 *end() const
    {
        return rows + sizeof(rows) / sizeof(rows[0]);
    }
    union
    {
        vec4 rows[4]{};
        float data[16];
    };

    friend constexpr mat4x4 operator*(const mat4x4 &lhs, const mat4x4 &rhs)
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

    constexpr static mat4x4 get_rotation_matrix(vec3 euler_angles)
    {
        auto x_rad{radians(euler_angles.x)};
        auto y_rad{radians(euler_angles.y)};
        auto z_rad{radians(euler_angles.x)};

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
};

constexpr mat4x4 get_project_matrix(float n, float f, float l, float r, float b, float t)
{
    return mat4x4{
        vec4{-2.0f * n / (r - l), 0, -(r + l) / (r - l), 0},
        vec4{0, -2.0f / (t - b), -(t + b) / (t - b), 0},
        vec4{0, 0, (f + n) / (f - b), 2.0f * n * f / (f - n)},
        vec4{0, 0, 1, 0},
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

constexpr mat4x4 rotate(float angle)
{
    // FIXME: Test rotation about x axis
    return mat4x4{
        vec4{std::cos(radians(angle)), -std::sin(radians(angle)), 0, 0},
        vec4{std::sin(radians(angle)), std::cos(radians(angle)), 0, 0},
        vec4{0, 0, 1, 0},
        vec4{0, 0, 0, 1},
    };
}

constexpr inline mat4x4 mat4x4::I = {
    vec4{1, 0, 0, 0},
    vec4{0, 1, 0, 0},
    vec4{0, 0, 1, 0},
    vec4{0, 0, 0, 1},
};
