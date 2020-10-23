//
// Created by lepouki on 10/23/2020.
//

#include "lepong/Graphics/Quad.h"

namespace lepong::Graphics
{

///
/// Creates a quad mesh and sets its vertex layout to the provided layout.
///
LEPONG_NODISCARD static Mesh MakeQuadWithLayout(const Vertices& vertices, const VertexLayout& vertexLayout) noexcept;

Mesh MakeSimpleQuad() noexcept
{
    const Vertices kVertices =
    {
        -0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f
    };

    const VertexLayout kVertexLayout = { 2 };

    return MakeQuadWithLayout(kVertices, kVertexLayout);
}

Mesh MakeQuadWithLayout(const Vertices& vertices, const VertexLayout& vertexLayout) noexcept
{
    const Indices kIndices =
    {
        0, 1, 2,
        0, 2, 3
    };

    Mesh newMesh = MakeMesh(vertices, kIndices);

    if (newMesh.va)
    {
        const VertexLayout kVertexLayout = { 2 };
        SetMeshVertexLayout(newMesh, kVertexLayout);
    }

    return newMesh;
}

Mesh MakeTextureReadyQuad() noexcept
{
    const Vertices kVertices =
    {
        -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, 1.0f, 0.0f
    };

    const VertexLayout kVertexLayout = { 2, 2 };

    return MakeQuadWithLayout(kVertices, kVertexLayout);
}

} // namespace lepong::Graphics
