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

void Ball::CollideAgainstTerrain(const Vector2i& winSize) noexcept
{
    const auto kCollidesTop = (position.y > static_cast<float>(winSize.y) - radius) && (moveDirection.y > 0);
    const auto kCollidesBottom = (position.y < radius) && (moveDirection.y < 0);

    if (kCollidesTop || kCollidesBottom)
    {
        moveDirection.y = -moveDirection.y;
    }
}

bool Ball::CollideAgainst(const Paddle& paddle) noexcept
{
    auto collides = false;

    const auto kInRangeY =
        position.y < (paddle.position.y + paddle.size.y / 2.0f) &&
        position.y > (paddle.position.y - paddle.size.y / 2.0f);

    if (kInRangeY)
    {
        const Vector2f kBallProjectedOnPaddle =
        {
            paddle.position.x + (paddle.size.x / 2.0f) * paddle.front,
            position.y
        };

        const Vector2f kPaddleToBall = position - kBallProjectedOnPaddle;
        const auto kRadiusSquared = radius * radius;

        if (kPaddleToBall.SquareMag() < kRadiusSquared)
        {
            collides = true;
            OnPaddleCollision(paddle);
        }
    }

    return collides;
}

void Ball::OnPaddleCollision(const Paddle& paddle) noexcept
{
    moveSpeed += 50.0f;
    moveDirection = Normalize(position - paddle.position);
}

Side Ball::GetTouchingSide(const Vector2i& winSize) const noexcept
{
    Side side = Side::None;

    if (position.x < radius)
    {
        side = Side::Player1;
    }
    else if (position.x > static_cast<float>(winSize.x) - radius)
    {
        side = Side::Player2;
    }

    return side;
}

void Ball::Reset(const Vector2i& winSize) noexcept
{
    position = { winSize.x / 2.0f, winSize.y / 2.0f };

    moveSpeed = 0.0f;
    moveDirection = { 0.0f, 0.0f };
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
