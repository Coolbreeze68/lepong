//
// Created by lepouki on 10/23/2020.
//

#pragma once

#include "lepong/Math/Vector2.h"

#include "Mesh.h"

namespace lepong::Graphics
{

///
/// Creates a simple quad mesh.
///
LEPONG_NODISCARD Mesh MakeSimpleQuad() noexcept;

///
/// Creates a quad mesh with texture data.
///
LEPONG_NODISCARD Mesh MakeTextureReadyQuad() noexcept;

///
/// Creates a quad vertex shader.<br><br>
///
/// This vertex shader requires the following uniforms to be loaded:<br>
/// - <b>uWinSize</b>: The size of the render window in pixels.<br>
/// - <b>uSize</b>: The size of the quad in pixels.<br>
/// - <b>uPosition</b>: The position of the quad in pixels.<br><br>
///
/// Rendering is pretty simple, this is pong after all.
///
LEPONG_NODISCARD GLuint MakeQuadVertexShader() noexcept;

///
/// Same as above but also passes texture data to the fragment shader.
///
LEPONG_NODISCARD GLuint MakeTextureReadyQuadVertexShader() noexcept;

///
/// Draws a quad using the provided program.<br>
/// This function expects the program to be using a vertex shader created with <i>MakeQuadVertexShader</i>.<br>
/// That is a lot of arguments, feels bad man.
///
void DrawQuad(const Mesh& quad, const Vector2f& size, const Vector2f& position, GLuint program) noexcept;

} // namespace lepong::Graphics
