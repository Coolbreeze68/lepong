//
// Created by lepouki on 10/12/2020.
//

#pragma once

#include <Windows.h>

#include "Attribute.h"

#include "Math/Vector2.h"

namespace lepong::Window
{

///
/// A key input callback.
///
using PFNKeyCallback = void (*)(int key, bool pressed);

///
/// Initializes the window system.<br>
/// If the window system is already initialized, this function returns false.
///
/// \param callback The function called to process window events.
/// \return Whether the system was successfully initialized.
///
bool Init() noexcept;

///
/// Sets the function to be called when a key input message is sent to the window.<br>
/// Calling this function with nullptr disables the key callback.
///
/// \param callback The new key callback.
///
void SetKeyCallback(PFNKeyCallback callback) noexcept;

///
/// Cleans up all resources used by the window system.<br>
/// If the window system is not initialized, this function does nothing.
///
void Cleanup() noexcept;

///
/// Creates a window with the provided size and title.<br>
/// Not storing the returned window handle results in a memory leak.
///
/// \return The newly created window or <code>nullptr</code> if the window system is not initialized.
///
LEPONG_NODISCARD HWND MakeWindow(const Vector2i& size, const wchar_t* title) noexcept;

///
/// Destroys the provided window.
///
/// \param window The window to destroy.
///
void DestroyWindow(HWND window) noexcept;

///
/// Sets the provided window's resizable state.
///
/// \param window The window the change the resizable state of.
/// \param resizable Whether the window should be resizable.
///
void SetWindowResizable(HWND window, bool resizable) noexcept;

} // namespace lepong::Window
