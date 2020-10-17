//
// Created by lepouki on 10/17/2020.
//

#pragma once

#include <GL/GL.h>

///
/// Not defined for some reason.
///
using GLchar = char;

namespace lepong::Graphics::GL
{

enum : GLenum
{
    ARRAY_BUFFER         = 0x8892,
    ELEMENT_ARRAY_BUFFER = 0x8893,
    FRAGMENT_SHADER      = 0x8B30,
    VERTEX_SHADER        = 0x8B31,
    COMPILE_STATUS       = 0x8B81,
    LINK_STATUS          = 0x8B82
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

} // namespace lepong::Graphics::GL
