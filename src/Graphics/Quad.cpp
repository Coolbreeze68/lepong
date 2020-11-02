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
        SetMeshVertexLayout(newMesh, vertexLayout);
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

GLuint MakeQuadVertexShader() noexcept
{
    constexpr auto kSource =
    R"(

    #version 330 core

    layout (location = 0) in vec2 aPosition;

    uniform vec2 uWinSize;

    uniform vec2 uSize;
    uniform vec2 uPosition;

    void main()
    {
        vec2 position = (aPosition * uSize) + uPosition;
        gl_Position = vec4(position * 2.0 / uWinSize - vec2(1.0, 1.0), 0.0, 1.0);
    }

    )";

    return Graphics::CreateShaderFromSource(gl::VertexShader, kSource);
}

GLuint MakeTextureReadyQuadVertexShader() noexcept
{
    constexpr auto kSource =
    R"(

    #version 330 core

    layout (location = 0) in vec2 aPosition;
    layout (location = 1) in vec2 aTexturePosition;

    out vec2 vTexturePosition;

    uniform vec2 uWinSize;

    uniform vec2 uSize;
    uniform vec2 uPosition;

    void main()
    {
        vec2 position = (aPosition * uSize) + uPosition;
        gl_Position = vec4(position * 2.0 / uWinSize - vec2(1.0), 0.0, 1.0);
        vTexturePosition = aTexturePosition;
    }

    )";

    return Graphics::CreateShaderFromSource(gl::VertexShader, kSource);
}

void DrawQuad(const Mesh& quad, const Vector2f& size, const Vector2f& position, GLuint program) noexcept
{
    gl::UseProgram(program);

    const auto kSizeLocation = gl::GetUniformLocation(program, "uSize");
    const auto kPositionLocation = gl::GetUniformLocation(program, "uPosition");

    gl::Uniform2f(kSizeLocation, size.x, size.y);
    gl::Uniform2f(kPositionLocation, position.x, position.y);

    Graphics::DrawMesh(quad);
}

} // namespace lepong::Graphics
