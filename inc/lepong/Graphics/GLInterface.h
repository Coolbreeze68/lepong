//
// Created by lepouki on 10/17/2020.
//

#pragma once

// See the bottom of the file for the namespace alias.

#include <cstdint>

#include <Windows.h> // Needed by "GL.h".
#include <GL/GL.h>

#include "Namespace.h"

using GLchar = char;
using GLsizeiptr = std::uintptr_t;

namespace lepong::Graphics::GL
{

enum : GLenum
{
    False              = 0,
    Float              = 0x1406,
    ArrayBuffer        = 0x8892,
    ElementArrayBuffer = 0x8893,
    FragmentShader     = 0x8B30,
    VertexShader       = 0x8B31,
    CompileStatus      = 0x8B81,
    LinkStatus         = 0x8B82
};

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
///
GLuint CreateShader(GLenum shaderType) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml
///
void DeleteShader(GLuint shader) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glShaderSource.xhtml
///
void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCompileShader.xhtml
///
void CompileShader(GLuint shader) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetShader.xhtml
///
void GetShaderiv(GLuint shader, GLenum pname, GLint* params) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetShaderInfoLog.xhtml
///
void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml
///
GLuint CreateProgram() noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteProgram.xhtml
///
void DeleteProgram(GLuint program) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
///
void AttachShader(GLuint program, GLuint shader) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
///
void LinkProgram(GLuint program) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgram.xhtml
///
void GetProgramiv(GLuint program, GLenum pname, GLint* params) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgramInfoLog.xhtml
///
void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
///
void UseProgram(GLuint program) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
///
void GenVertexArrays(GLsizei n, GLuint* arrays) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteVertexArrays.xhtml
///
void DeleteVertexArrays(GLsizei n, const GLuint* arrays) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindVertexArray.xhtml
///
void BindVertexArray(GLuint array) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenBuffers.xhtml
///
void GenBuffers(GLsizei n, GLuint* buffers) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDeleteBuffers.xhtml
///
void DeleteBuffers(GLsizei n, const GLuint* buffers) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
///
void BindBuffer(GLenum target, GLuint buffer) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBufferData.xhtml
///
void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnableVertexAttribArray.xhtml
///
void EnableVertexAttribArray(GLuint index) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
///
void VertexAttribPointer(
    GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) noexcept;

} // namespace lepong::Graphics::GL

LEPONG_DECL_GL_NAMESPACE_ALIAS;