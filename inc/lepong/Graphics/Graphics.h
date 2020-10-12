//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include "Context.h"

namespace lepong::Graphics
{

///
/// Initializes the resources used by the graphics system.<br>
/// If the graphics system is already initialized, this function returns false.
///
/// \return Whether the graphics system was successfully initialized.
///
bool Init() noexcept;

///
/// \return Whether the graphics system is initialized.
///
bool IsInitialized() noexcept;

///
/// Cleans up all resources used by the graphics system.<br>
/// If the graphics system is not initialized, this function does nothing.
///
void Cleanup() noexcept;

} // namespace lepong::Graphics
