//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include <Windows.h>

#include "Math/Vector2.h"

namespace lepong::Window
{

///
/// Initializes the window system.<br>
/// If the window system is already initialized, this function returns false.
///
/// \param callback The function called to process window events.
/// \return Whether the system was successfully initialized.
///
bool Init(WNDPROC callback) noexcept;

///
/// Cleans up all resources used by the window system.<br>
/// If the window system is not initialized, this function does nothing.
///
void Cleanup() noexcept;

///
/// Creates a window with the provided <i>size</i> and <i>title</i>.
///
/// \return The newly created window or <code>nullptr</code> if the window system is not initialized.
///
HWND MakeWindow(const Vector2i& size, const wchar_t* title) noexcept;

///
/// Destroys the provided window.
///
/// \param window The window to destroy.
///
void DestroyWindow(HWND window) noexcept;

} // namespace lepong::Window
