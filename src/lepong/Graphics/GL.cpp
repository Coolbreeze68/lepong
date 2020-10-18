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
LEPONG_DECL_OPENGL_FUNCTION(glCreateProgram);
LEPONG_DECL_OPENGL_FUNCTION(glDeleteProgram);
LEPONG_DECL_OPENGL_FUNCTION(glAttachShader);
LEPONG_DECL_OPENGL_FUNCTION(glLinkProgram);
LEPONG_DECL_OPENGL_FUNCTION(glGetProgramiv);
LEPONG_DECL_OPENGL_FUNCTION(glGetProgramInfoLog);
LEPONG_DECL_OPENGL_FUNCTION(glUseProgram);
LEPONG_DECL_OPENGL_FUNCTION(glGenVertexArrays);
LEPONG_DECL_OPENGL_FUNCTION(glDeleteVertexArrays);
LEPONG_DECL_OPENGL_FUNCTION(glBindVertexArray);
LEPONG_DECL_OPENGL_FUNCTION(glGenBuffers);
LEPONG_DECL_OPENGL_FUNCTION(glDeleteBuffers);
LEPONG_DECL_OPENGL_FUNCTION(glBindBuffer);
LEPONG_DECL_OPENGL_FUNCTION(glBufferData);
LEPONG_DECL_OPENGL_FUNCTION(glEnableVertexAttribArray);
LEPONG_DECL_OPENGL_FUNCTION(glVertexAttribPointer);

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
        LEPONG_LOAD_OPENGL_FUNCTION(glGetShaderInfoLog) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glCreateProgram) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glDeleteProgram) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glAttachShader) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glLinkProgram) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glGetProgramiv) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glGetProgramInfoLog) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glUseProgram) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glGenVertexArrays) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glDeleteVertexArrays) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glBindVertexArray) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glGenBuffers) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glDeleteBuffers) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glBindBuffer) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glBufferData) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glEnableVertexAttribArray) &&
        LEPONG_LOAD_OPENGL_FUNCTION(glVertexAttribPointer);
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

GLuint CreateProgram() noexcept
{
    return glCreateProgram();
}

void DeleteProgram(GLuint program) noexcept
{
    glDeleteProgram(program);
}

void AttachShader(GLuint program, GLuint shader) noexcept
{
    glAttachShader(program, shader);
}

void LinkProgram(GLuint program) noexcept
{
    glLinkProgram(program);
}

void GetProgramiv(GLuint program, GLenum pname, GLint* params) noexcept
{
    glGetProgramiv(program, pname, params);
}

void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) noexcept
{
    glGetProgramInfoLog(program, maxLength, length, infoLog);
}

void UseProgram(GLuint program) noexcept
{
    glUseProgram(program);
}

void GenVertexArrays(GLsizei n, GLuint* arrays) noexcept
{
    glGenVertexArrays(n, arrays);
}

void DeleteVertexArrays(GLsizei n, const GLuint* arrays) noexcept
{
    glDeleteVertexArrays(n, arrays);
}

void BindVertexArray(GLuint array) noexcept
{
    glBindVertexArray(array);
}

void GenBuffers(GLsizei n, GLuint* buffers) noexcept
{
    glGenBuffers(n, buffers);
}

void DeleteBuffers(GLsizei n, const GLuint* buffers) noexcept
{
    glDeleteBuffers(n, buffers);
}

void BindBuffer(GLenum target, GLuint buffer) noexcept
{
    glBindBuffer(target, buffer);
}

void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) noexcept
{
    glBufferData(target, size, data, usage);
}

void EnableVertexAttribArray(GLuint index) noexcept
{
    glEnableVertexAttribArray(index);
}

void VertexAttribPointer(
    GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) noexcept
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

} // namespace lepong::Graphics::GL
