//
// Created by lepouki on 11/2/2020.
//

#pragma once

#include "lepong/Graphics/GL.h"
#include "lepong/Graphics/Mesh.h"

#include "GameObject.h"
#include "Paddle.h"

namespace lepong
{

enum class Side
{
    None    = -1,
    Player1 =  0,
    Player2 =  1
};

class Ball : public GameObject
{
public:
    float radius;

public:
    Ball(float radius, Graphics::Mesh& mesh, GLuint& program) noexcept;

public:
    void Render() const noexcept;

public:
    void CollideAgainstTerrain(const Vector2i& winSize) noexcept;

    ///
    /// \return Whether the ball is colliding with the paddle.
    ///
    LEPONG_NODISCARD bool CollideAgainst(const Paddle& paddle) noexcept;

public:
    ///
    /// \return The side the ball is touching.<br>
    /// If the ball is not touching any side, this function returns <code>Side::None</code>.
    ///
    LEPONG_NODISCARD Side GetTouchingSide(const Vector2i& winSize) const noexcept;

public:
    ///
    /// Resets the ball to its default state.
    ///
    void Reset(const Vector2i& winSize) noexcept;

private:
    Graphics::Mesh& mMesh;
    GLuint& mProgram;

private:
    void OnPaddleCollision(const Paddle& paddle) noexcept;
};

///
/// A fragment shader that renders a circle. This shader requires texture data.
///
LEPONG_NODISCARD GLuint MakeBallFragmentShader() noexcept;

} // namespace lepong
