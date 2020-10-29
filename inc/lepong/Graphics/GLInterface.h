//
// Created by lepouki on 10/17/2020.
//

#pragma once

#include <cstdint>

#include <Windows.h> // Needed by "GL.h".
#include <GL/GL.h>

#include "lepong/Attribute.h"

using GLchar = char;
using GLsizeiptr = std::uintptr_t;

namespace lepong::Graphics::GL
{

enum : GLenum
{
    False              = 0,
    Triangles          = 0x0004,
    UnsignedInt        = 0x1405,
    Float              = 0x1406,
    Vendor             = 0x1F00,
    Renderer           = 0x1F01,
    Version            = 0x1F02,
    ArrayBuffer        = 0x8892,
    ElementArrayBuffer = 0x8893,
    StaticDraw         = 0x88E4,
    FragmentShader     = 0x8B30,
    VertexShader       = 0x8B31,
    CompileStatus      = 0x8B81,
    LinkStatus         = 0x8B82,
    InfoLogLength      = 0x8B84
};

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glCreateShader.xhtml
///
LEPONG_NODISCARD GLuint CreateShader(GLenum shaderType) noexcept;

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
LEPONG_NODISCARD GLuint CreateProgram() noexcept;

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

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawArrays.xhtml
///
void DrawArrays(GLenum mode, GLint first, GLsizei count) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDrawElements.xhtml
///
void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) noexcept;

///
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetString.xhtml
///
LEPONG_NODISCARD const GLubyte* GetString(GLenum name) noexcept;

} // namespace lepong::Graphics::GL
