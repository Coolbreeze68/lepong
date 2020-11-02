//
// Created by lepouki on 11/2/2020.
//

#pragma once

#include "lepong/Math/Vector2.h"

namespace lepong
{

class GameObject
{
public:
    Vector2f position;

    float moveSpeed = 0;
    Vector2f moveDirection;

public:
    virtual void Update(float delta) noexcept;
};

} // namespace lepong
