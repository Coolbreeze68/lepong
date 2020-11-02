//
// Created by lepouki on 11/2/2020.
//

#include "lepong/Graphics/Quad.h"

#include "lepong/Game/Ball.h"

namespace lepong
{

Ball::Ball(float radius, Graphics::Mesh& mesh, GLuint& program) noexcept
    : mMesh(mesh)
    , mProgram(program)
    , radius(radius)
{
}

void Ball::Render() const noexcept
{
    Graphics::DrawQuad(mMesh, Vector2f{ radius, radius }, position, mProgram);
}

void Ball::Update(float delta) noexcept
{
    GameObject::Update(delta);
}

GLuint MakeBallFragmentShader() noexcept
{
    constexpr auto kSource =
    R"(

    #version 330 core

    in vec2 vTexturePosition;

    out vec4 FragColor;

    void main()
    {
        vec2 normTexturePosition = vTexturePosition * 2.0 - vec2(1.0);
        float squareDistanceToCenter = dot(normTexturePosition, normTexturePosition);

        if (squareDistanceToCenter > 0.5)
        {
            discard;
        }

        // Simple glow.
        float intensity = 1.0 - 2.0 * squareDistanceToCenter;

        FragColor = vec4(vec3(intensity), 1.0);
    }

    )";

    return Graphics::CreateShaderFromSource(gl::FragmentShader, kSource);
}

} // namespace lepong
