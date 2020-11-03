//
// Created by lepouki on 11/2/2020.
//

#include <cmath>

#include "lepong/Math/Math.h"

namespace lepong
{

int RandomSign() noexcept
{
    return rand() > (RAND_MAX / 2) ? 1 : -1; // NOLINT: Don't need particularly good random.
}

float RandomSignFloat() noexcept
{
    return (float)RandomSign();
}

} // namespace lepong
