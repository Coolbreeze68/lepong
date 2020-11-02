//
// Created by lepouki on 11/2/2020.
//

#pragma once

#include "lepong/Graphics/GL.h"
#include "lepong/Graphics/Mesh.h"

#include "GameObject.h"

namespace lepong
{

class Ball : public GameObject
{
public:
    float radius;

public:
    Ball(float radius, Graphics::Mesh& mesh, GLuint& program) noexcept;

public:
    void Render() const noexcept;

private:
    Graphics::Mesh& mMesh;
    GLuint& mProgram;
};

///
/// A fragment shader that renders a circle. This shader requires texture data.
///
LEPONG_NODISCARD GLuint MakeBallFragmentShader() noexcept;

} // namespace lepong
