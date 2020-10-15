//
// Created by lepouki on 10/15/2020.
//

#pragma once

#include <Windows.h>

namespace lepong::Graphics
{

using PFNwglChoosePixelFormatARB = BOOL (*)(HDC, const int*, const FLOAT*, UINT, int*, UINT*);
using PFNwglCreateContextAttribsARB = BOOL (*)(HDC, HGLRC, const int*);

///
/// Returns a pointer to the provided OpenGL function.
///
/// \param name The name of the function to load.
/// \return The function pointer corresponding to the provided function name.
///
PROC LoadOpenGLFunction(const char* name) noexcept;

} // namespace lepong::Graphics
