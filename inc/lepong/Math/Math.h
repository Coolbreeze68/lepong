//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include "lepong/Attribute.h"

#include "Vector2.h"

namespace lepong
{

///
/// \return Randomly <code>1</code> or <code>-1</code>.
///
LEPONG_NODISCARD int RandomSign() noexcept;

///
/// \return Randomly <code>1.0f</code> or <code>-1.0f</code>.
///
LEPONG_NODISCARD float RandomSignFloat() noexcept;

} // namespace lepong
