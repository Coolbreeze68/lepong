//
// Created by lepouki on 10/24/2020.
//

#pragma once

#include <cstdint>

#include <type_traits>

#include "Vector4.h"

#include "lepong/Attribute.h"

namespace lepong
{

template<typename Scalar, std::enable_if_t<std::is_arithmetic_v<Scalar>, int> = 0>
class Matrix4
{
public:
    using RowType = Vector4<Scalar>;

public:
    constexpr Matrix4(
        const RowType& r0,
        const RowType& r1,
        const RowType& r2,
        const RowType& r3
    ) noexcept
        : mData{ r0, r1, r2, r3 }
    {
    }

    constexpr Matrix4(
        Scalar v00, Scalar v01, Scalar v02, Scalar v03,
        Scalar v10, Scalar v11, Scalar v12, Scalar v13,
        Scalar v20, Scalar v21, Scalar v22, Scalar v23,
        Scalar v30, Scalar v31, Scalar v32, Scalar v33
    ) noexcept
        : mData{ { v00, v01, v02, v03 }, { v10, v11, v12, v13 }, { v20, v21, v22, v23 }, { v30, v31, v32, v33 } }
    {
    }

    ///
    /// Constructs a matrix with its diagonal values set to the provided value.
    ///
    constexpr explicit Matrix4(Scalar value) noexcept
        : Matrix4{ { value, 0, 0, 0 }, { 0, value, 0, 0 }, { 0, 0, value, 0 }, { 0, 0, 0, value } }
    {
    }

public:
    // Unchecked bounds.
    constexpr RowType& operator[](std::size_t index) noexcept
    {
        return mData[index];
    }

    // Unchecked bounds.
    constexpr const RowType& operator[](std::size_t index) const noexcept
    {
        return mData[index];
    }

    LEPONG_NODISCARD constexpr Scalar* Data() noexcept
    {
        return &(mData->x);
    }

    LEPONG_NODISCARD constexpr const Scalar* Data() const noexcept
    {
        return &(mData->x);
    }

private:
    RowType mData[4];
};

using Matrix4f = Matrix4<float>;
using Matrix4i = Matrix4<int>;
using Matrix4u = Matrix4<unsigned>;

template<typename Scalar>
LEPONG_NODISCARD constexpr Matrix4<Scalar> Transpose(const Matrix4<Scalar>& matrix) noexcept
{
    return
    {
        matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
        matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
        matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
        matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3],
    };
}

template<typename Scalar>
LEPONG_NODISCARD constexpr Matrix4<Scalar> operator*(const Matrix4<Scalar>& a, const Matrix4<Scalar>& b) noexcept
{
    const auto kAr0 = a[0];
    const auto kAr1 = a[1];
    const auto kAr2 = a[2];
    const auto kAr3 = a[3];

    const auto kBT = Transpose(b);

    const auto kBc0 = kBT[0];
    const auto kBc1 = kBT[1];
    const auto kBc2 = kBT[2];
    const auto kBc3 = kBT[3];

    return
    {
        Dot(kAr0, kBc0), Dot(kAr0, kBc1), Dot(kAr0, kBc2), Dot(kAr0, kBc3),
        Dot(kAr1, kBc0), Dot(kAr1, kBc1), Dot(kAr1, kBc2), Dot(kAr1, kBc3),
        Dot(kAr2, kBc0), Dot(kAr2, kBc1), Dot(kAr2, kBc2), Dot(kAr2, kBc3),
        Dot(kAr3, kBc0), Dot(kAr3, kBc1), Dot(kAr3, kBc2), Dot(kAr3, kBc3)
    };
}

template<typename Scalar>
LEPONG_NODISCARD constexpr Vector4<Scalar> operator*(const Matrix4<Scalar>& a, const Vector4<Scalar>& b) noexcept
{
    return
    {
        Dot(a[0], b),
        Dot(a[1], b),
        Dot(a[2], b),
        Dot(a[3], b)
    };
}

} // namespace lepong
