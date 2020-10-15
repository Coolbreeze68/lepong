//
// Created by lepouki on 10/15/2020.
//

#pragma once

#include <Windows.h>

#include <GL/GL.h>

#include "lepong/Attribute.h"

namespace lepong::Graphics::GL
{

struct Context
{
    HWND targetWindow = nullptr;
    HDC device = nullptr;
    HGLRC context = nullptr;
};

///
/// Loads all the functions required by the OpenGL interface.<br>
/// If the OpenGL interface is already initialized, this function returns false.
///
/// \return Whether the OpenGL interface was successfully initialized.
///
LEPONG_NODISCARD bool Init() noexcept;

///
/// Doesn't do anything.<br>
/// This is just here for the system lifetime management in "lepong.cpp".
///
void Cleanup() noexcept;

///
/// Creates an OpenGL context for the provided window with the latest version available.<br>
/// Not storing the returned context results in a memory leak.
///
/// \return The newly created context.
///
LEPONG_NODISCARD Context MakeContext(HWND window) noexcept;

///
/// Sets the provided context as the current OpenGL context.
///
void MakeContextCurrent(const Context& context) noexcept;

///
/// Swaps the front and back buffers for the provided context.
///
void SwapBuffers(const Context& context) noexcept;

///
/// Destroys the provided context.<br>
/// Hmm yes useful documentation me like.
///
/// \param context The context to destroy.
///
void DestroyContext(const Context& context) noexcept;

// The following functions act as an OpenGL interface

} // namespace lepong::Graphics::GL
