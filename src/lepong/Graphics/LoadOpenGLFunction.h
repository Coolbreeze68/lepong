//
// Created by lepouki on 10/15/2020.
//

#pragma once

#include <Windows.h>

#include "lepong/Graphics/GLInterface.h"

namespace lepong::Graphics
{

// wgl extensions.

using PFNwglChoosePixelFormatARB = BOOL (WINAPI*)(HDC, const int*, const FLOAT*, UINT, int*, UINT*);
using PFNwglCreateContextAttribsARB = HGLRC (WINAPI*)(HDC, HGLRC, const int*);

// OpenGL extensions.

using PFNglCreateShader = GLuint (*)(GLenum);
using PFNglDeleteShader = void (*)(GLuint);
using PFNglShaderSource = void (*)(GLuint, GLsizei, const GLchar**, const GLint*);
using PFNglCompileShader = void (*)(GLuint);
using PFNglGetShaderiv = void (*)(GLuint, GLenum, GLint*);
using PFNglGetShaderInfoLog = void (*)(GLuint, GLsizei, GLsizei*, GLchar*);
using PFNglCreateProgram = GLuint (*)();
using PFNglDeleteProgram = void (*)(GLuint);
using PFNglAttachShader = void (*)(GLuint, GLuint);
using PFNglLinkProgram = void (*)(GLuint);
using PFNglGetProgramiv = void (*)(GLuint, GLenum, GLint*);
using PFNglGetProgramInfoLog = void (*)(GLuint, GLsizei, GLsizei*, GLchar*);
using PFNglUseProgram = void (*)(GLuint);
using PFNglGenVertexArrays = void (*)(GLsizei, GLuint*);
using PFNglDeleteVertexArrays = void (*)(GLsizei, const GLuint*);
using PFNglBindVertexArray = void (*)(GLuint);
using PFNglGenBuffers = void (*)(GLsizei, GLuint*);
using PFNglDeleteBuffers = void (*)(GLsizei, const GLuint*);
using PFNglBindBuffer = void (*)(GLenum, GLuint);
using PFNglBufferData = void (*)(GLenum, GLsizeiptr, const void*, GLenum);
using PFNglEnableVertexAttribArray = void (*)(GLuint);
using PFNglVertexAttribPointer = void (*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);

///
/// Returns a pointer to the provided OpenGL function.
///
/// \param name The name of the function to load.
/// \return The function pointer corresponding to the provided function name.
///
PROC LoadOpenGLFunction(const char* name) noexcept;

} // namespace lepong::Graphics
