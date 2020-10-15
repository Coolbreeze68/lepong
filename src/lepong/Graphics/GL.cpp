//
// Created by lepouki on 10/15/2020.
//

#include "LoadOpenGLFunction.h"

#include "lepong/Graphics/GL.h"

namespace lepong::Graphics::GL
{

///
/// Load all the OpenGL functions required by the graphics system.
///
/// \return Whether all the required OpenGL functions were successfully loaded.
///
LEPONG_NODISCARD static bool LoadRequiredOpenGLFunctions() noexcept;

bool Init() noexcept
{
    // Create dummy context
    // LoadRequiredOpenGLFunctions
    // Destroy dummy context

    return true;
}

#define LEPONG_DECL_OPENGL_FUNCTION(name) \
    static PFN##name name = nullptr

LEPONG_DECL_OPENGL_FUNCTION(wglChoosePixelFormatARB);
LEPONG_DECL_OPENGL_FUNCTION(wglCreateContextAttribsARB);

#define LEPONG_LOAD_OPENGL_FUNCTION(name) \
    (name = reinterpret_cast<PFN##name>(LoadOpenGLFunction(#name)))

bool LoadRequiredOpenGLFunctions() noexcept
{
    return
        LEPONG_LOAD_OPENGL_FUNCTION(wglChoosePixelFormatARB) &&
        LEPONG_LOAD_OPENGL_FUNCTION(wglCreateContextAttribsARB);
}

void Cleanup() noexcept
{
}

} // namespace lepong::Graphics::GL
