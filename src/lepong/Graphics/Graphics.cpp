//
// Created by lepouki on 10/12/2020.
//

#include <memory>
#include <iostream>

#include <Windows.h>

#include "LoadOpenGLFunction.h"

#include "lepong/Assert.h"
#include "lepong/Log.h"

#include "lepong/Graphics/Graphics.h"

namespace lepong::Graphics
{

static HMODULE sOpenGLLibrary = nullptr;

bool Init() noexcept
{
    LEPONG_ASSERT_OR_RETURN_VAL(!sOpenGLLibrary, false);

    sOpenGLLibrary = LoadLibraryA("OpenGL32.dll");
    return sOpenGLLibrary;
}

void Cleanup() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sOpenGLLibrary);

    FreeLibrary(sOpenGLLibrary);
    sOpenGLLibrary = nullptr;
}

///
/// I wonder what this function does.
///
LEPONG_NODISCARD static bool ShaderCompileFailed(GLuint shader) noexcept;

///
/// I love documentation.
///
static void LogShaderInfo(GLuint shader) noexcept;

GLuint CreateShaderFromSource(GLenum type, const char* source) noexcept
{
    LEPONG_ASSERT_OR_RETURN_VAL(source, 0);
    LEPONG_ASSERT_OR_RETURN_VAL(type == gl::VertexShader || type == gl::FragmentShader, 0);

    GLuint shader = gl::CreateShader(type);

    gl::ShaderSource(shader, 1, &source, nullptr);
    gl::CompileShader(shader);

    if (ShaderCompileFailed(shader))
    {
        LogShaderInfo(shader);

        gl::DeleteShader(shader);
        shader = 0;
    }

    return shader;
}

bool ShaderCompileFailed(GLuint shader) noexcept
{
    GLint compileStatus;
    gl::GetShaderiv(shader, gl::CompileStatus, &compileStatus);
    return !compileStatus;
}

void LogShaderInfo(GLuint shader) noexcept
{
    GLint infoLogLength = 0;
    gl::GetShaderiv(shader, gl::InfoLogLength, &infoLogLength);

    const auto kInfoLog = std::make_unique<GLchar[]>(infoLogLength);
    const auto kInfoLogData = kInfoLog.get();

    gl::GetShaderInfoLog(shader, infoLogLength, nullptr, kInfoLogData);

    Log::Log("Shader compile error:");
    Log::Log(kInfoLogData);
}

///
/// I wonder what this function does.
///
LEPONG_NODISCARD static bool ProgramLinkFailed(GLuint program) noexcept;

///
/// I love documentation.
///
static void LogProgramInfo(GLuint program) noexcept;

GLuint CreateProgramFromShaders(GLuint vertex, GLuint fragment) noexcept
{
    LEPONG_ASSERT_OR_RETURN_VAL(vertex && fragment, 0);

    GLuint program = gl::CreateProgram();

    gl::AttachShader(program, vertex);
    gl::AttachShader(program, fragment);

    gl::LinkProgram(program);

    if (ProgramLinkFailed(program))
    {
        LogProgramInfo(program);

        gl::DeleteProgram(program);
        program = 0;
    }

    return program;
}

bool ProgramLinkFailed(GLuint program) noexcept
{
    GLint linkStatus;
    gl::GetProgramiv(program, gl::LinkStatus, &linkStatus);
    return !linkStatus;
}

void LogProgramInfo(GLuint program) noexcept
{
    GLint infoLogLength = 0;
    gl::GetProgramiv(program, gl::InfoLogLength, &infoLogLength);

    auto infoLog = std::make_unique<GLchar[]>(infoLogLength);
    auto rawInfoLog = infoLog.get();

    gl::GetProgramInfoLog(program, infoLogLength, nullptr, rawInfoLog);

    Log::Log("Program link error:");
    Log::Log(rawInfoLog);
}

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

} // namespace lepong::Graphics
