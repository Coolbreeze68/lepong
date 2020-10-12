//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include <type_traits>

namespace lepong
{

template<typename Scalar, std::enable_if_t<std::is_arithmetic_v<Scalar>, int> = 0>
struct Vector2
{
    Scalar x;
    Scalar y;
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned>;

} // namespace lepong
