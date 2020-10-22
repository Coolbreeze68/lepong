//
// Created by lepouki on 10/15/2020.
//

#pragma once

#include "GL.h"

#include "lepong/Attribute.h"

namespace gl = lepong::Graphics::GL;

namespace lepong::Graphics
{

///
/// Initializes the resources used by the graphics system.<br>
/// If the graphics system is already initialized, this function returns false.
///
/// \return Whether the graphics system was successfully initialized.
///
LEPONG_NODISCARD bool Init() noexcept;

///
/// Cleans up all resources used by the graphics system.<br>
/// If the graphics system is not initialized, this function does nothing.
///
void Cleanup() noexcept;

///
/// Creates a shader using the provided source code.<br>
///
/// If <i>type</i> is not <code>gl::VertexShader</code> or <code>gl::FragmentShader</code> or if <i>source</i> is
/// <code>nullptr</code>, the return value is 0.<br>
///
/// If compilation fails, the return value is 0 and the error is automatically logged.
///
LEPONG_NODISCARD GLuint CreateShaderFromSource(GLenum type, const char* source) noexcept;

///
/// Creates a program using the provided vertex and fragment shaders.<br>
/// This function does not check if the provided shaders are valid vertex and fragment shaders.<br>
///
/// If the shaders are 0, the return value is 0.<br>
/// If linking fails, the return value is 0 and the error is automatically logged.
///
LEPONG_NODISCARD GLuint CreateProgramFromShaders(GLuint vert, GLuint frag) noexcept;

} // namespace lepong::Graphics
