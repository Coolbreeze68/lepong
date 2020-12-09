//
// Created by lepouki on 11/2/2020.
//

#include <Windows.h>

#include "lepong/Check.h"
#include "lepong/Time/Time.h"

namespace lepong::Time
{

static bool sInitialized = false;

static LARGE_INTEGER sInitTimestamp;
static LARGE_INTEGER sPerformanceFrequency;

bool Init() noexcept
{
    LEPONG_CHECK_OR_RETURN_VAL(!sInitialized, false);

    sInitialized = true;

    QueryPerformanceCounter(&sInitTimestamp);
    QueryPerformanceFrequency(&sPerformanceFrequency);

    return sInitialized;
}

void Cleanup() noexcept
{
    sInitialized = false;

    // Nothing to do here.
}

float Get() noexcept
{
    LEPONG_CHECK_OR_RETURN_VAL(sInitialized, 0.0);

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    const auto kTickDelta = now.QuadPart - sInitTimestamp.QuadPart;
    return static_cast<float>(kTickDelta) / sPerformanceFrequency.QuadPart;
}

} // namespace lepong::Time
