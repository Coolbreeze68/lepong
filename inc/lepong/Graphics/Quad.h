//
// Created by lepouki on 10/23/2020.
//

#pragma once

#include "Mesh.h"

namespace lepong::Graphics
{

///
/// Creates a simple quad mesh.
///
LEPONG_NODISCARD Mesh MakeSimpleQuad() noexcept;

///
/// Creates a quad mesh with texture data.
///
LEPONG_NODISCARD Mesh MakeTextureReadyQuad() noexcept;



} // namespace lepong::Graphics
