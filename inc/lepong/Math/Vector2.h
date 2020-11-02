//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include <cmath>

#include <type_traits>

#include "lepong/Attribute.h"

namespace lepong
{

template<typename Scalar, std::enable_if_t<std::is_arithmetic_v<Scalar>, int> = 0>
struct Vector2
{
    Scalar x = 0;
    Scalar y = 0;

public:
    constexpr Vector2 operator*=(Scalar s) const noexcept
    {
        x *= s;
        y *= s;

        return *this;
    }

    constexpr Vector2 operator/=(Scalar s) const noexcept
    {
        x /= s;
        y /= s;

        return *this;
    }

    constexpr Vector2& operator+=(const Vector2& other) noexcept
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    LEPONG_NODISCARD constexpr Vector2 operator*(Scalar s) const noexcept
    {
        return { x * s, y * s };
    }

    LEPONG_NODISCARD constexpr Vector2 operator/(Scalar s) const noexcept
    {
        return { x / s, y / s };
    }

    LEPONG_NODISCARD constexpr Vector2 operator-() const noexcept
    {
        return { -x, -y };
    }

    LEPONG_NODISCARD constexpr Vector2 operator-(const Vector2& other) const noexcept
    {
        return { x - other.x, y - other.y };
    }

public:
    LEPONG_NODISCARD constexpr float Mag() const noexcept
    {
        const auto kSqMag = (float)SquareMag();
        return sqrtf(kSqMag);
    }

    LEPONG_NODISCARD constexpr Scalar SquareMag() const noexcept
    {
        return (x * x) + (y * y);
    }
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

LEPONG_NODISCARD constexpr Vector2f Normalize(const Vector2f& v) noexcept
{
    return v / v.Mag();
}

} // namespace lepong
