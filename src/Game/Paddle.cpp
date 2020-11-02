//
// Created by lepouki on 11/2/2020.
//

#include "lepong/Graphics/Quad.h"

#include "lepong/Game/Paddle.h"

namespace lepong
{

Paddle::Paddle(const Vector2f& size, float front, Graphics::Mesh& mesh, GLuint& program) noexcept
    : mMesh(mesh)
    , mProgram(program)
    , size(size)
    , front(front)
{
}

void Paddle::Render() const noexcept
{
    Graphics::DrawQuad(mMesh, size, position, mProgram);
}

void Paddle::Update(float delta) noexcept
{
    GameObject::Update(delta);
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
