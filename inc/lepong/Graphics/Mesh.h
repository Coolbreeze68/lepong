//
// Created by lepouki on 10/23/2020.
//

#pragma once

#include <vector>

#include "Graphics.h"

namespace lepong::Graphics
{

///
/// A struct holding mesh data handles.
///
struct Mesh
{
    GLuint va = 0;
    GLuint vb = 0;
    GLuint ib = 0;

    GLuint numIndices = 0;

public:
    LEPONG_NODISCARD constexpr bool IsValid() const noexcept
    {
        return va;
    }
};

///
/// Mesh vertices.
///
using Vertices = std::vector<GLfloat>;

///
/// Mesh indices.
///
using Indices = std::vector<GLuint>;

///
/// Mesh vertex layout. Yeah.
///
using VertexLayout = std::vector<GLuint>;

///
/// Creates a mesh with the provided data.
///
LEPONG_NODISCARD Mesh MakeMesh(const Vertices& vertices, const Indices& indices) noexcept;

///
/// Sets the provided mesh's vertex layout.<br>
/// If the provided mesh is not valid, this function does nothing.
///
void SetMeshVertexLayout(const Mesh& mesh, const VertexLayout& vertexLayout) noexcept;

///
/// Draws the provided mesh using the current program.<br>
/// If the provided mesh is not valid, this function does nothing.
///
void DrawMesh(const Mesh& mesh) noexcept;

///
/// Draws the provided mesh using the provided program.<br>
/// If the provided mesh or the provided program is not valid, this function does nothing.
///
void DrawMesh(const Mesh& mesh, GLuint program) noexcept;

///
/// Destroys resources associated with the provided mesh.<br>
/// If the provided mesh is not valid, this function does nothing.
///
void DestroyMesh(Mesh& mesh) noexcept;

} // namespace lepong::Graphics
