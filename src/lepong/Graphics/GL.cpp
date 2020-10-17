//
// Created by lepouki on 10/15/2020.
//

#include "Extensions.h"
#include "LoadOpenGLFunction.h"

#include "lepong/Assert.h"
#include "lepong/Window.h"

#include "lepong/Graphics/GL.h"

namespace lepong::Graphics::GL
{

static bool sInitialized = false;

///
/// Creates a dummy OpenGL context.
///
LEPONG_NODISCARD static Context MakeFakeContextForDummyWindow() noexcept;

///
/// Load all the OpenGL functions required by the graphics system.
///
/// \return Whether all the required OpenGL functions were successfully loaded.
///
LEPONG_NODISCARD static bool LoadRequiredOpenGLFunctions() noexcept;

bool Init() noexcept
{
    LEPONG_ASSERT_OR_RETURN_VAL(!sInitialized, false);

    const auto kFakeContext = MakeFakeContextForDummyWindow();
    MakeContextCurrent(kFakeContext);

    sInitialized = LoadRequiredOpenGLFunctions();

    DestroyContext(kFakeContext);
    Window::DestroyWindow(kFakeContext.targetWindow);

    return sInitialized;
}

///
/// Sets a dummy pixel format for the provided device.
///
static void SetDummyPixelFormat(HDC device) noexcept;

Context MakeFakeContextForDummyWindow() noexcept
{
    const auto kDummyWindow = Window::MakeWindow(Vector2i{ 0, 0 }, L"");
    const auto kDC = GetDC(kDummyWindow);

    SetDummyPixelFormat(kDC);

    return
    {
        kDummyWindow,
        kDC,
        wglCreateContext(kDC)
    };
}

void SetDummyPixelFormat(HDC device) noexcept
{
    constexpr PIXELFORMATDESCRIPTOR kPixelFormat =
    {
        sizeof(kPixelFormat),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // NOLINT: Clang-Tidy, A Love Letter.
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    const auto kFormatIndex = ChoosePixelFormat(device, &kPixelFormat);
    SetPixelFormat(device, kFormatIndex, nullptr);
}

// OpenGL functions.

#define LEPONG_DECL_OPENGL_FUNCTION(name) \
    static PFN##name name = nullptr

#define LEPONG_LOAD_OPENGL_FUNCTION(name) \
    (name = reinterpret_cast<PFN##name>(LoadOpenGLFunction(#name)))

LEPONG_DECL_OPENGL_FUNCTION(wglChoosePixelFormatARB);
LEPONG_DECL_OPENGL_FUNCTION(wglCreateContextAttribsARB);
LEPONG_DECL_OPENGL_FUNCTION(glCreateShader);
LEPONG_DECL_OPENGL_FUNCTION(glDeleteShader);
LEPONG_DECL_OPENGL_FUNCTION(glShaderSource);
LEPONG_DECL_OPENGL_FUNCTION(glCompileShader);
LEPONG_DECL_OPENGL_FUNCTION(glGetShaderiv);
LEPONG_DECL_OPENGL_FUNCTION(glGetShaderInfoLog);

bool LoadRequiredOpenGLFunctions() noexcept
{
    return
        LEPONG_LOAD_OPENGL_FUNCTION(wglChoosePixelFormatARB) &&
        LEPONG_LOAD_OPENGL_FUNCTION(wglCreateContextAttribsARB) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glCreateShader) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glDeleteShader) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glShaderSource) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glCompileShader) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glGetShaderiv) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glGetShaderInfoLog);
}

void Cleanup() noexcept
{
    // Nothing to do here.
}

///
/// Creates an advanced OpenGL context.<br>
/// I love useful documentation.
///
LEPONG_NODISCARD static HGLRC MakeAdvancedContext(HDC device) noexcept;

Context MakeContext(HWND window) noexcept
{
    const auto kDC = GetDC(window);

    return
    {
        window,
        kDC,
        MakeAdvancedContext(kDC)
    };
}

///
/// Sets a more advanced pixel format for the provided device.
///
static void SetAdvancedPixelFormat(HDC device) noexcept;

HGLRC MakeAdvancedContext(HDC device) noexcept
{
    SetAdvancedPixelFormat(device);

    constexpr int kAttributes[] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 1, // Context version 1.0 creates a context with the latest version.
        WGL_CONTEXT_MINOR_VERSION_ARB, 0, // ^
        0
    };

    return wglCreateContextAttribsARB(device, nullptr, kAttributes);
}

void SetAdvancedPixelFormat(HDC device) noexcept
{
    constexpr int kAttributes[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };

    int formatIndex;
    LEPONG_MAYBE_UNUSED UINT numFormats;

    wglChoosePixelFormatARB(device, kAttributes, nullptr, 1, &formatIndex, &numFormats);
    SetPixelFormat(device, formatIndex, nullptr);
}

void MakeContextCurrent(const Context& context) noexcept
{
    wglMakeCurrent(context.device, context.context);
}

void SwapBuffers(const Context& context) noexcept
{
    wglSwapLayerBuffers(context.device, WGL_SWAP_MAIN_PLANE);
}

void DestroyContext(const Context& context) noexcept
{
    wglDeleteContext(context.context);
}

// OpenGL interface.

GLuint CreateShader(GLenum shaderType) noexcept
{
    return glCreateShader(shaderType);
}

void DeleteShader(GLuint shader) noexcept
{
    glDeleteShader(shader);
}

void ShaderSource(GLuint shader, GLsizei count, const GLchar** string, const GLint* length) noexcept
{
    glShaderSource(shader, count, string, length);
}

void CompileShader(GLuint shader) noexcept
{
    glCompileShader(shader);
}

void GetShaderiv(GLuint shader, GLenum pname, GLint* params) noexcept
{
    glGetShaderiv(shader, pname, params);
}

void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) noexcept
{
    glGetShaderInfoLog(shader, maxLength, length, infoLog);
}

} // namespace lepong::Graphics::GL
