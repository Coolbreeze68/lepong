//
// Created by lepouki on 10/12/2020.
//

#include <Windows.h>

#include "LoadOpenGLFunction.h"

#include "lepong/Assert.h"

namespace lepong::Graphics
{

static bool sInitialized = false;
static HMODULE sOpenGLLibrary = nullptr;

bool Init() noexcept
{
    if (sInitialized)
    {
        return false;
    }

    sOpenGLLibrary = LoadLibraryA("OpenGL32.dll");
    return sInitialized = sOpenGLLibrary;
}

bool IsInitialized() noexcept
{
    return sInitialized;
}

void Cleanup() noexcept
{
    if (sInitialized)
    {
        FreeLibrary(sOpenGLLibrary);
        sInitialized = false;
    }
}

namespace Internal
{

PROC LoadOpenGLFunction(const char* name) noexcept
{
    LEPONG_ASSERT(sInitialized, "can't load if the graphics system is not initialized");
    const auto kFunction = wglGetProcAddress(name);

    if (!kFunction)
    {
        return GetProcAddress(sOpenGLLibrary, name);
    }

    return kFunction;
}

} // namespace Internal

} // namespace lepong::Graphics
