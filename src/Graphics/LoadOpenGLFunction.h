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

using PFNglCreateShader = GLuint (WINAPI*)(GLenum);
using PFNglDeleteShader = void (WINAPI*)(GLuint);
using PFNglShaderSource = void (WINAPI*)(GLuint, GLsizei, const GLchar**, const GLint*);
using PFNglCompileShader = void (WINAPI*)(GLuint);
using PFNglGetShaderiv = void (WINAPI*)(GLuint, GLenum, GLint*);
using PFNglGetShaderInfoLog = void (WINAPI*)(GLuint, GLsizei, GLsizei*, GLchar*);
using PFNglCreateProgram = GLuint (WINAPI*)();
using PFNglDeleteProgram = void (WINAPI*)(GLuint);
using PFNglAttachShader = void (WINAPI*)(GLuint, GLuint);
using PFNglLinkProgram = void (WINAPI*)(GLuint);
using PFNglGetProgramiv = void (WINAPI*)(GLuint, GLenum, GLint*);
using PFNglGetProgramInfoLog = void (WINAPI*)(GLuint, GLsizei, GLsizei*, GLchar*);
using PFNglUseProgram = void (WINAPI*)(GLuint);
using PFNglGenVertexArrays = void (WINAPI*)(GLsizei, GLuint*);
using PFNglDeleteVertexArrays = void (WINAPI*)(GLsizei, const GLuint*);
using PFNglBindVertexArray = void (WINAPI*)(GLuint);
using PFNglGenBuffers = void (WINAPI*)(GLsizei, GLuint*);
using PFNglDeleteBuffers = void (WINAPI*)(GLsizei, const GLuint*);
using PFNglBindBuffer = void (WINAPI*)(GLenum, GLuint);
using PFNglBufferData = void (WINAPI*)(GLenum, GLsizeiptr, const void*, GLenum);
using PFNglEnableVertexAttribArray = void (WINAPI*)(GLuint);
using PFNglVertexAttribPointer = void (WINAPI*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
using PFNglGetUniformLocation = GLint (WINAPI*)(GLuint, const GLchar*);
using PFNglUniform2f = void (WINAPI*)(GLint, GLfloat, GLfloat);

///
/// Returns a pointer to the provided OpenGL function.
///
/// \param name The name of the function to load.
/// \return The function pointer corresponding to the provided function name.
///
PROC LoadOpenGLFunction(const char* name) noexcept;

} // namespace lepong::Graphics
