//
// Created by lepouki on 10/15/2020.
//

#pragma once

#include "GL.h"

#include "lepong/Attribute.h"

namespace gl = lepong::Graphics::GL;

namespace lepong::Graphics
{

///
/// Initializes the resources used by the graphics system.<br>
/// If the graphics system is already initialized, this function returns false.
///
/// \return Whether the graphics system was successfully initialized.
///
LEPONG_NODISCARD bool Init() noexcept;

///
/// Cleans up all resources used by the graphics system.<br>
/// If the graphics system is not initialized, this function does nothing.
///
void Cleanup() noexcept;

} // namespace lepong::Graphics
