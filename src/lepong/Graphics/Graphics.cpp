//
// Created by lepouki on 10/12/2020.
//

#include <Windows.h>

#include "LoadOpenGLFunction.h"

#include "lepong/Assert.h"

namespace lepong::Graphics
{

static HMODULE sOpenGLLibrary = nullptr;

bool Init() noexcept
{
    if (sOpenGLLibrary)
    {
        return false;
    }

    sOpenGLLibrary = LoadLibraryA("OpenGL32.dll");

    LEPONG_ASSERT_OR_RETURN(sOpenGLLibrary,
        false,
        "Failed to load OpenGL");

    return true;
}

bool IsInitialized() noexcept
{
    return sOpenGLLibrary;
}

void Cleanup() noexcept
{
    if (sOpenGLLibrary)
    {
        FreeLibrary(sOpenGLLibrary);
        sOpenGLLibrary = nullptr;
    }
}

namespace Internal
{

PROC LoadOpenGLFunction(const char* name) noexcept
{
    const auto kFunction = wglGetProcAddress(name);

    if (!kFunction)
    {
        return GetProcAddress(sOpenGLLibrary, name);
    }

    return kFunction;
}

} // namespace Internal

} // namespace lepong::Graphics
