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
/// Logs a string message to the log file.
///
void Log(const char* message) noexcept;

///
/// Logs a formatted string to the log file.<br>
/// The provided format is assumed to be not nullptr and null-terminated.
///
template<typename... Args>
void Log(const char* format, Args&&... args) noexcept;

} // namespace lepong::Log

//-------------------- Implementation --------------------//

#include <cstdio>
#include <utility>

namespace lepong::Log
{

template<typename... Args>
void Log(const char* format, Args&&... args) noexcept
{
    LEPONG_ASSERT_OR_RETURN(format);

    // This is very slow but it's definitely not a big concern.
    // I have no idea why we have to add 1 here.
    const auto kSize = snprintf(nullptr, 0, format, std::forward<Args>(args)...) + 1;

    const auto kMessage = new char[kSize + 1]; // Include the null terminator.
    kMessage[kSize] = '\0';

    // Log the message and cleanup.
    snprintf(kMessage, kSize, format, std::forward<Args>(args)...);
    Log(kMessage);

    delete[] kMessage;
}

} // namespace lepong::Log
