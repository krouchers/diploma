#include <stdexcept>
#include <cmath>
#include <numbers>

#include "log.hpp"

struct vec4
{

    constexpr vec4()
        : x{0}, y{0}, z{0}, w{0} {};
    constexpr vec4(float x, float y, float z, float w)
        : x{x}, y{y}, z{z}, w{w} {};

    float &operator[](int i)
    {
        if (!(i >= 0 && i <= 4))
        {
            throw std::out_of_range("Out of range indexing in vec4");
        }
        return data[i];
    }

    constexpr bool operator==(const vec4 &rhs) const
    {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z &&
               w == rhs.w;
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
            float x, y, z, w;
        };

        float data[4];
    };
};

struct mat4x4
{
    static const mat4x4 I;
    // mat4x4() = default;
    // {
    //     *this = I;
    // }

    // constexpr mat4x4()
    // {
    //     *this = I;
    // }
    constexpr mat4x4()
    {
        *this = I;
    }

    constexpr mat4x4(
        std::initializer_list<vec4> il) : rows{}
    {
        for (std::size_t i = 0; i < il.size(); ++i)
        {
            rows[i] = *(il.begin() + i);
        }
    }

    constexpr bool operator==(const mat4x4 &rhs) const
    {
        for (std::size_t i = 0; i < 4; ++i)
            if (rows[i] != rhs.rows[i])
                return false;
        return true;
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
        vec4 rows[4];
        float data[16];
    };
};

constexpr float radians(float degrees)
{
    return degrees * std::numbers::pi / 180.f;
}

constexpr mat4x4 get_project_matrix(float n, float f, float l, float r, float b, float t)
{
    return mat4x4{
        vec4{-2.0f * n / (r - l), 0, -(r + l) / (r - l), 0},
        vec4{0, -2.0f / (t - b), -(t + b) / (t - b), 0},
        vec4{0, 0, (f + n) / (f - b), 2.0f * n * f / (f - n)},
        vec4{0, 0, 1, 0},
    };
}

constexpr mat4x4 get_projection_matrix(float n, float f, float l, float r, float b, float t)
{
    return mat4x4{
        vec4{-2.0f * n / (r - l), 0, -(r + l) / (r - l), 0},
        vec4{0, -2.0f / (t - b), -(t + b) / (t - b), 0},
        vec4{0, 0, (f + n) / (f - b), 2.0f * n * f / (f - n)},
        vec4{0, 0, 1, 0},
    };
}

constexpr mat4x4 get_translation_matrix(const vec4 &v)
{
    return mat4x4{
        vec4{1, 0, 0, v.x},
        vec4{0, 1, 0, v.y},
        vec4{0, 0, 1, v.z},
        vec4{0, 0, 0, 1},
    };
}

constexpr mat4x4 get_rotation_matrix(float angle)
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
