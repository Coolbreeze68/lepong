//
// Created by lepouki on 10/24/2020.
//

#pragma once

#include <type_traits>

#include "lepong/Attribute.h"

namespace lepong
{

template<typename Scalar, std::enable_if_t<std::is_arithmetic_v<Scalar>, int> = 0>
struct Vector4
{
    Scalar x = 0;
    Scalar y = 0;
    Scalar z = 0;
    Scalar w = 0;

public:
    // Unchecked bounds.
    constexpr Scalar& operator[](std::size_t index) noexcept
    {
        return (&x)[index];
    }

    // Unchecked bounds.
    constexpr const Scalar& operator[](std::size_t index) const noexcept
    {
        return (&x)[index];
    }

    constexpr Vector4 operator*=(Scalar s) const noexcept
    {
        x *= s;
        y *= s;
        z *= s;
        w *= s;

        return *this;
    }

    constexpr Vector4 operator/=(Scalar s) const noexcept
    {
        x /= s;
        y /= s;
        z /= s;
        w /= s;

        return *this;
    }

    LEPONG_NODISCARD constexpr Vector4 operator*(Scalar s) const noexcept
    {
        return { x * s, y * s, z * s, w * s };
    }

    LEPONG_NODISCARD constexpr Vector4 operator/(Scalar s) const noexcept
    {
        return { x / s, y / s, z / s, w / s };
    }
};

using Vector4f = Vector4<float>;
using Vector4i = Vector4<int>;
using Vector4u = Vector4<unsigned>;

template<typename Scalar>
LEPONG_NODISCARD constexpr Scalar Dot(const Vector4<Scalar>& a, const Vector4<Scalar>& b) noexcept
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

} // namespace lepong
