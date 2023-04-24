#pragma once
#include "math/common.hpp"
#include <cmath>

namespace math
{
    template <size_t dim>
    struct Vec
    {
        constexpr float &operator[](int i)
        {
            return data[i];
        }

        constexpr float operator[](int i) const
        {
            return data[i];
        }

        constexpr bool operator==(const Vec &rhs) const
        {
            for (size_t i{0}; i < dim; ++i)
                if (std::abs(data[i] - rhs[i]) < kEps)
                    return false;
            return true;
        }

        constexpr bool operator!=(const Vec &rhs) const
        {
            return !(*this == rhs);
        }

        constexpr Vec &operator*=(const float k)
        {
            for (auto &elem : data)
            {
                elem *= k;
            }

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

        float data[dim];
    };

    template <size_t dim>
    Vec<dim> operator*(const float k, const Vec<dim> &rhs)
    {
        Vec<dim> res{};
        for (int i{0}; i < dim; ++i)
            res[i] = k * rhs[i];

        return res;
    }

    template <size_t dim>
    Vec<dim> operator*(const Vec<dim> &rhs, const float k)
    {
        return k * rhs;
    }

    template <size_t dim>
    Vec<dim> operator/(const Vec<dim> &rhs, const float k)
    {
        return (1.f / k) * rhs;
    }

    template <size_t dim>
    Vec<dim> operator/(const float k, const Vec<dim> &rhs)
    {
        return rhs / k;
    }
}