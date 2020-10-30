//
// Created by lepouki on 10/23/2020.
//

#include <numeric>

#include "lepong/Assert.h"

#include "lepong/Graphics/Mesh.h"

namespace lepong::Graphics
{

///
/// Loads the mesh data to the mesh.
///
static void LoadMeshData(Mesh& mesh, const Vertices& vertices, const Indices& indices) noexcept;

Mesh MakeMesh(const Vertices& vertices, const Indices& indices) noexcept
{
    Mesh mesh = {};
    gl::GenVertexArrays(1, &mesh.va);

    if (mesh.va)
    {
        gl::BindVertexArray(mesh.va);
        LoadMeshData(mesh, vertices, indices);
    }

    return mesh;
}

///
/// I wonder what this does.
///
static void LoadVertexData(Mesh& mesh, const Vertices& vertices) noexcept;

///
/// Loads the indices to the mesh.
///
static void LoadIndexData(Mesh& mesh, const Indices& indices) noexcept;

void LoadMeshData(Mesh& mesh, const Vertices& vertices, const Indices& indices) noexcept
{
    LoadVertexData(mesh, vertices);
    LoadIndexData(mesh, indices);
}

void LoadVertexData(Mesh& mesh, const Vertices& vertices) noexcept
{
    gl::GenBuffers(1, &mesh.vb);
    gl::BindBuffer(gl::ArrayBuffer, mesh.vb);

    using ValueType = Vertices::value_type;
    gl::BufferData(gl::ArrayBuffer, sizeof(ValueType) * vertices.size(), vertices.data(), gl::StaticDraw);
}

void LoadIndexData(Mesh& mesh, const Indices& indices) noexcept
{
    gl::GenBuffers(1, &mesh.ib);
    gl::BindBuffer(gl::ElementArrayBuffer, mesh.ib);

    using ValueType = Indices::value_type;
    gl::BufferData(gl::ElementArrayBuffer, sizeof(ValueType) * indices.size(), indices.data(), gl::StaticDraw);

    mesh.numIndices = indices.size();
}

void SetMeshVertexLayout(const Mesh& mesh, const VertexLayout& vertexLayout) noexcept
{
    LEPONG_ASSERT_OR_RETURN(mesh.va);

    gl::BindVertexArray(mesh.va);

    const auto kStride = std::accumulate(vertexLayout.begin(), vertexLayout.end(), 0u) * sizeof(GLfloat);
    GLsizeiptr attributeOffset = 0;

    for (GLuint i = 0; i < vertexLayout.size(); ++i)
    {
        gl::EnableVertexAttribArray(i);

        const auto kAttributeSize = vertexLayout[i];
        gl::VertexAttribPointer(i, kAttributeSize, gl::Float, gl::False, kStride, (void*)attributeOffset);

        attributeOffset += kAttributeSize * sizeof(GLfloat);
    }
}

void DrawMesh(const Mesh& mesh) noexcept
{
    LEPONG_ASSERT_OR_RETURN(mesh.va);

    gl::BindBuffer(gl::ElementArrayBuffer, mesh.ib);
    gl::BindVertexArray(mesh.va);
    gl::DrawElements(gl::Triangles, mesh.numIndices, gl::UnsignedInt, nullptr);
}

void DrawMesh(const Mesh& mesh, GLuint program) noexcept
{
    LEPONG_ASSERT_OR_RETURN(mesh.va && program);

    gl::UseProgram(program);
    DrawMesh(mesh);
}

void DestroyMesh(Mesh& mesh) noexcept
{
    LEPONG_ASSERT_OR_RETURN(mesh.va);

    gl::DeleteVertexArrays(1, &mesh.va);
    mesh.va = 0;

    const GLuint kBuffers[] = { mesh.vb, mesh.ib };
    gl::DeleteBuffers(2, kBuffers);
}

} // namespace lepong::Graphics
