//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include <Windows.h>

#include "lepong/Attribute.h"

namespace lepong::Graphics::Internal
{

///
/// \param name The name of the function to load.
/// \return The function pointer corresponding to the provided function name.
///
LEPONG_NODISCARD PROC LoadOpenGLFunction(const char* name) noexcept;

} // namespace lepong::Graphics::Internal
