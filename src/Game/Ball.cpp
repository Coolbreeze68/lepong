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

void Ball::CollideWithTerrain(const Vector2i& winSize) noexcept
{
    const auto kCollidesTop = (position.y > static_cast<float>(winSize.y) - radius) && (moveDirection.y > 0);
    const auto kCollidesBottom = (position.y < radius) && (moveDirection.y < 0);

    if (kCollidesTop || kCollidesBottom)
    {
        moveDirection.y = -moveDirection.y;
    }
}

bool Ball::CollideWith(const Paddle& paddle) noexcept
{
    // Over-engineered collision code below.

    // If the ball is moving toward the paddle, the sign of its x direction is opposite to
    // the way the paddle is facing.
    const auto kMovingToward = (moveDirection.x * paddle.forward) < 0.0f;

    if (!kMovingToward)
    {
        // This avoids potential collision jitter.
        return false;
    }

    // Ignore cases where the ball is behind the paddle.
    const auto kBehind = IsBehind(paddle);

    if (kBehind)
    {
        // This avoids cases where the ball still goes toward the player goal after bouncing.
        return false;
    }

    return DoCollideWith(paddle);
}

Side Ball::GetTouchingSide(const Vector2i& winSize) const noexcept
{
    auto side = Side::None;

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

bool Ball::IsBehind(const Paddle& paddle) const noexcept
{
    // We don't use the whole radius to avoid the ball from going through the paddle.
    // This means we don't cover all possible situations but this is good enough.
    const auto kOuterEdge = position.x + (radius * 0.25f) * -paddle.forward;

    const auto kPaddleFrontEdge = paddle.position.x + (paddle.size.x / 2.0f) * paddle.forward;

    if (paddle.forward > 0.0f)
    {
        return kOuterEdge < kPaddleFrontEdge;
    }
    else
    {
        return kOuterEdge > kPaddleFrontEdge;
    }
}

bool Ball::DoCollideWith(const Paddle& paddle) noexcept
{
    auto collides = false;

    // An extra zone that extends the paddle. Makes gameplay less punishing.
    const auto kPaddleGraceZone = paddle.size.y * 0.1f;

    const auto kInRangeY =
        position.y < (paddle.position.y + paddle.size.y / 2.0f + kPaddleGraceZone) &&
        position.y > (paddle.position.y - paddle.size.y / 2.0f - kPaddleGraceZone);

    if (kInRangeY)
    {
        const auto kRadiusSquared = radius * radius;

        const Vector2f kCenterProjectedOnPaddle = { paddle.position.x + (paddle.size.x / 2.0f) * paddle.forward, position.y };
        const Vector2f kPaddleToBall = position - kCenterProjectedOnPaddle;

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

        FragColor = vec4(intensity);
    }

    )";

    return Graphics::CreateShaderFromSource(gl::FragmentShader, kSource);
}

} // namespace lepong
