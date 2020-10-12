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
    LEPONG_ASSERT_OR_RETURN_VAL(!sOpenGLLibrary, false);

    sOpenGLLibrary = LoadLibraryA("OpenGL32.dll");
    return sOpenGLLibrary;
}

bool IsInitialized() noexcept
{
    return sOpenGLLibrary;
}

void Cleanup() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sOpenGLLibrary);

    FreeLibrary(sOpenGLLibrary);
    sOpenGLLibrary = nullptr;
}

namespace Internal
{

PROC LoadOpenGLFunction(const char* name) noexcept
{
    LEPONG_ASSERT_OR_RETURN_VAL(sOpenGLLibrary && name, nullptr);

    const auto kFunction = wglGetProcAddress(name);

    if (!kFunction)
    {
        return GetProcAddress(sOpenGLLibrary, name);
    }

    return kFunction;
}

} // namespace Internal

} // namespace lepong::Graphics
