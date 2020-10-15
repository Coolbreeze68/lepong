//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include "Assert.h"
#include "Attribute.h"

namespace lepong::Log
{

///
/// Initializes the log file.<br>
/// If the log file is already initialized, this function returns false.
///
/// \return Whether the log file was successfully initialized.
///
LEPONG_NODISCARD bool Init() noexcept;

///
/// Cleans up the log file.<br>
/// Not cleaning up the log file results in a memory leak.
///
void Cleanup() noexcept;

///
/// Logs message to the log file.
///
void Log(const char* message) noexcept;

} // namespace lepong::Log
