//
// Created by lepouki on 11/2/2020.
//

#pragma once

#include "lepong/Attribute.h"

namespace lepong::Time
{

///
/// \return Whether the time system was successfully initialized.
///
LEPONG_NODISCARD bool Init() noexcept;

///
/// Cleans up resources used by the time system.
///
void Cleanup() noexcept;

///
/// If the time system is not initialized, this function returns 0.
///
/// \return The time since initialization in seconds.
///
LEPONG_NODISCARD float Get() noexcept;

} // namespace lepong::Time
