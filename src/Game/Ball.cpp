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
    const auto kDiameter = radius * 2.0f;
    Graphics::DrawQuad(mMesh, Vector2f{ kDiameter, kDiameter }, position, mProgram);
}

void Ball::Update(float delta) noexcept
{
    GameObject::Update(delta);
}

void Ball::CollideAgainstTerrain(const Vector2i& winSize) noexcept
{
    const auto kCollidesTop = (position.y > static_cast<float>(winSize.y) - radius) && (moveDirection.y > 0);
    const auto kCollidesBottom = (position.y < radius) && (moveDirection.y < 0);

    if (kCollidesTop || kCollidesBottom)
    {
        moveDirection.y = -moveDirection.y;
    }
}

void Ball::CollideAgainst(const Paddle& paddle) noexcept
{

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

        // Simple glow.
        float intensity = 1.0 - squareDistanceToCenter;

        FragColor = vec4(vec3(intensity), 1.0);
    }

    )";

    return Graphics::CreateShaderFromSource(gl::FragmentShader, kSource);
}

} // namespace lepong
