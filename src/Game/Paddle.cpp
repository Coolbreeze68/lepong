//
// Created by lepouki on 11/2/2020.
//

#include "lepong/Graphics/Quad.h"

#include "lepong/Game/Paddle.h"

namespace lepong
{

Paddle::Paddle(const Vector2f& size, Graphics::Mesh& mesh, GLuint& program) noexcept
    : mMesh(mesh)
    , mProgram(program)
    , size(size)
{
}

void Paddle::Render() const noexcept
{
    Graphics::DrawQuad(mMesh, size, position, mProgram);
}

GLuint MakePaddleFragmentShader() noexcept
{
    constexpr auto kSource =
    R"(

    #version 330 core

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }

    )";

    return Graphics::CreateShaderFromSource(gl::FragmentShader, kSource);
}

} // namespace lepong
