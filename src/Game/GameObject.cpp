//
// Created by lepouki on 11/2/2020.
//

#include "lepong/Game/GameObject.h"

namespace lepong
{

void GameObject::Update() noexcept
{
    position += (moveDirection * moveSpeed);
}

} // namespace lepong
