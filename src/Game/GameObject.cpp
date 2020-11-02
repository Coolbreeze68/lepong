//
// Created by lepouki on 11/2/2020.
//

#include "lepong/Game/GameObject.h"

namespace lepong
{

void GameObject::Update(float delta) noexcept
{
    position += moveDirection * (moveSpeed * delta);
}

} // namespace lepong
