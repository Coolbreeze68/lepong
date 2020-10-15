//
// Created by lepouki on 10/15/2020.
//

#pragma once

#include "lepong/Attribute.h"

namespace lepong::Graphics::GL
{

///
/// Loads all the functions required by the OpenGL interface.
///
/// \return Whether the OpenGL interface was successfully initialized.
///
LEPONG_NODISCARD bool Init() noexcept;

///
/// Doesn't do anything.<br>
/// This is just here for the system lifetime management in "lepong.cpp".
///
void Cleanup() noexcept;

} // namespace lepong::Graphics::GL
