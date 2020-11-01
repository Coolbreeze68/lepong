//
// Created by lepouki on 10/12/2020.
//

#include <cstdint>

#include <iostream> // Debug

#include "lepong/Assert.h"
#include "lepong/Attribute.h"
#include "lepong/lepong.h"
#include "lepong/Log.h"
#include "lepong/Window.h"

#include "lepong/Graphics/Graphics.h"
#include "lepong/Graphics/Quad.h"

namespace lepong
{

static constexpr Vector2i skWinSize = { 1280, 720 };

static auto sInitialized = false;

static HWND sWindow;
static gl::Context sContext;

static GLuint sPaddleProgram;
static Graphics::Mesh sQuad;

///
/// A class holding the init and cleanup functions of any item.
///
class Lifetime
{
public:
    ///
    /// A generic initialization function.<br>
    /// Initialization functions must return false on failure.
    ///
    using PFNInit = bool (*)();

    ///
    /// A generic cleanup function.
    ///
    using PFNCleanup = void (*)();

public:
    ///
    /// Both init and cleanup functions must be provided.
    ///
    constexpr Lifetime(PFNInit init, PFNCleanup cleanup) noexcept
        : mInit(init), mCleanup(cleanup)
    {
    }

public:
    ///
    /// Pretty straight forward.
    ///
    /// \return Whether the item was successfully initialized.
    ///
    LEPONG_NODISCARD constexpr bool Init() const noexcept
    {
        return mInit();
    }

    ///
    /// Pretty straight forward.
    ///
    constexpr void Cleanup() const noexcept
    {
        mCleanup();
    }

private:
    PFNInit mInit;
    PFNCleanup mCleanup;
};

///
/// Initializes the game's systems.
///
LEPONG_NODISCARD static bool InitGameSystems() noexcept;

///
/// Cleans up the game's systems.
///
static void CleanupGameSystems() noexcept;

///
/// Initializes the game's state and resources.
///
LEPONG_NODISCARD static bool InitState() noexcept;

///
/// Cleans up the game's state and resources.
///
static void CleanupState() noexcept;

///
/// All the game's lifetimes.
///
static constexpr Lifetime kGameLifetimes[] =
{
    { InitGameSystems, CleanupGameSystems },
    { InitState, CleanupState }
};

///
/// A wrapper for the pretty ugly array reference syntax.
///
template<typename T, std::size_t Size>
using ConstArrayReference = const T (&)[Size];

///
/// Tries to run all the provided lifetime initialization functions.<br>
/// If an initialization function fails, the cleanup functions of the initialized items are called in reverse order.
///
/// \return Whether all the items have been successfully initialized.
///
template<std::size_t NumItems>
LEPONG_NODISCARD static bool TryInitItems(ConstArrayReference<Lifetime, NumItems> lifetimes) noexcept;

bool Init() noexcept
{
    LEPONG_ASSERT_OR_RETURN_VAL(!sInitialized, false);

    sInitialized = TryInitItems(kGameLifetimes);
    return sInitialized;
}

///
/// Cleans up all the items starting from the item at the provided index.<br>
/// Items are cleaned up in reverse order.
///
/// \param index The index of the first system to cleanup.
///
template<std::size_t NumItems>
static void CleanupItemsStartingAt(ConstArrayReference<Lifetime, NumItems> lifetimes, unsigned index) noexcept;

template<std::size_t NumItems>
bool TryInitItems(ConstArrayReference<Lifetime, NumItems> lifetimes) noexcept
{
    auto succeeded = true;

    for (unsigned i = 0; succeeded && i < NumItems; ++i)
    {
        succeeded = lifetimes[i].Init();

        if (!succeeded)
        {
            CleanupItemsStartingAt(lifetimes, i);
        }
    }

    return succeeded;
}

template<std::size_t NumItems>
void CleanupItemsStartingAt(ConstArrayReference<Lifetime, NumItems> lifetimes, unsigned index) noexcept
{
    for (auto i = static_cast<int>(index) - 1; i >= 0; --i)
    {
        lifetimes[i].Cleanup();
    }
}

///
/// All the system lifetimes.
///
static constexpr Lifetime kSystemLifetimes[] =
{
    { Log::Init, Log::Cleanup },
    { Window::Init, Window::Cleanup },
    { Graphics::Init, Graphics::Cleanup },
    { gl::Init, gl::Cleanup }
};

bool InitGameSystems() noexcept
{
    return TryInitItems(kSystemLifetimes);
}

///
/// Calls the cleanup function of all the provided item lifetimes.
///
template<std::size_t NumItems>
static void CleanupItems(ConstArrayReference<Lifetime, NumItems> itemLifetimes) noexcept;

void CleanupGameSystems() noexcept
{
    CleanupItems(kSystemLifetimes);
}

template<std::size_t NumItems>
void CleanupItems(ConstArrayReference<Lifetime, NumItems> itemLifetimes) noexcept
{
    CleanupItemsStartingAt(itemLifetimes, NumItems);
}

///
/// \return Whether the game window was successfully initialized.
///
LEPONG_NODISCARD static bool InitGameWindow() noexcept;

///
/// Cleans up the game window.
///
static void CleanupGameWindow() noexcept;

///
/// \return Whether the rendering context was successfully initialized.
///
LEPONG_NODISCARD static bool InitContext() noexcept;

///
/// Cleans up the rendering context.
///
static void CleanupContext() noexcept;

///
/// \return Whether the graphics resources were successfully initialized.
///
LEPONG_NODISCARD static bool InitGraphicsResources() noexcept;

///
/// Cleans up the graphics resources.
///
static void CleanupGraphicsResources() noexcept;

///
/// All the game state lifetimes.
///
static constexpr Lifetime kStateLifetimes[] =
{
    { InitGameWindow, CleanupGameWindow },
    { InitContext, CleanupContext },
    { InitGraphicsResources, CleanupGraphicsResources },
};

bool InitState() noexcept
{
    return TryInitItems(kStateLifetimes);
}

///
/// \param key The pressed key's virtual key code.
/// \param pressed Whether the key was pressed.
///
static void OnKeyEvent(int key, bool pressed) noexcept;

bool InitGameWindow() noexcept
{
    Window::SetKeyCallback(OnKeyEvent);
    sWindow = Window::MakeWindow(skWinSize, L"lepong");
    return sWindow;
}

static Vector2f sPaddlePosition = { 0, 0 };

void OnKeyEvent(int key, bool pressed) noexcept
{
    if (pressed)
    {
        if (key == VK_LEFT)
        {
            sPaddlePosition.x -= 50;
        }
        else if (key == VK_RIGHT)
        {
            sPaddlePosition.x += 50;
        }
    }
}

void CleanupGameWindow() noexcept
{
    Window::DestroyWindow(sWindow);
}

bool InitContext() noexcept
{
    sContext = gl::MakeContext(sWindow);
    const auto kValid = sContext.IsValid();

    if (kValid)
    {
        gl::MakeContextCurrent(sContext);
    }

    return kValid;
}

void CleanupContext() noexcept
{
    gl::DestroyContext(sContext);
}

///
/// \return Can you guess?
///
LEPONG_NODISCARD static bool InitPaddleProgram() noexcept;

///
/// You guessed it.
///
static void CleanupPaddleProgram() noexcept;

///
/// Oh boy.
///
LEPONG_NODISCARD static bool InitQuad() noexcept;

///
/// This is getting tedious.
///
static void CleanupQuad() noexcept;

///
/// All the graphics resource lifetimes.
///
static constexpr Lifetime kGraphicsResourceLifetimes[] =
{
    { InitPaddleProgram, CleanupPaddleProgram },
    { InitQuad, CleanupQuad }
};

bool InitGraphicsResources() noexcept
{
    return TryInitItems(kGraphicsResourceLifetimes);
}

///
/// \return A generic object vertex shader.
///
static GLuint CreateObjectVertShader() noexcept;

///
/// \return The paddle fragment shader. Unbelievable.
///
static GLuint CreatePaddleFragShader() noexcept;

///
/// Loads the window size value into the corresponding uniform in the provided program.
///
static void LoadWinSizeUniform(GLuint program) noexcept;

bool InitPaddleProgram() noexcept
{
    const auto kVert = CreateObjectVertShader();
    const auto kFrag = CreatePaddleFragShader();

    sPaddleProgram = Graphics::CreateProgramFromShaders(kVert, kFrag);

    gl::DeleteShader(kVert);
    gl::DeleteShader(kFrag);

    if (sPaddleProgram)
    {
        LoadWinSizeUniform(sPaddleProgram);
    }

    return sPaddleProgram;
}

GLuint CreateObjectVertShader() noexcept
{
    constexpr auto kSource =
    R"(

    #version 330 core

    layout (location = 0) in vec2 aPosition;

    uniform vec2 uWinSize;

    uniform vec2 uSize;
    uniform vec2 uPosition;

    void main()
    {
        vec2 position = (aPosition * uSize) + uPosition;
        gl_Position = vec4(position * 2.0 / uWinSize, 0.0, 1.0);
    }

    )";

    return Graphics::CreateShaderFromSource(gl::VertexShader, kSource);
}

GLuint CreatePaddleFragShader() noexcept
{
    constexpr auto kSource =
    R"(

    #version 330 core

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }

    )";

    return Graphics::CreateShaderFromSource(gl::FragmentShader, kSource);
}

void LoadWinSizeUniform(GLuint program) noexcept
{
    constexpr Vector2f kWinSize =
    {
        static_cast<float>(skWinSize.x),
        static_cast<float>(skWinSize.y)
    };

    gl::UseProgram(program);

    const auto kLocation = gl::GetUniformLocation(program, "uWinSize");
    gl::Uniform2f(kLocation, kWinSize.x, kWinSize.y);
}

void CleanupPaddleProgram() noexcept
{
    gl::DeleteProgram(sPaddleProgram);
}

bool InitQuad() noexcept
{
    sQuad = Graphics::MakeSimpleQuad();
    return sQuad.IsValid();
}

void CleanupQuad() noexcept
{
    Graphics::DestroyMesh(sQuad);
}

void CleanupGraphicsResources() noexcept
{
    CleanupItems(kGraphicsResourceLifetimes);
}

void CleanupState() noexcept
{
    CleanupItems(kStateLifetimes);
}

static auto sRunning = false;

///
/// Called before entering the main loop.
///
static void OnBeginRun() noexcept;

///
/// Called at each game update.
///
static void OnUpdate() noexcept;

///
/// Called at each game frame.
///
static void OnRender() noexcept;

///
/// Called when exiting the main loop.
///
static void OnFinishRun() noexcept;

void Run() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sInitialized && !sRunning);

    sRunning = true;
    OnBeginRun();

    while (sRunning)
    {
        OnUpdate();
        OnRender();
    }

    OnFinishRun();
}

///
/// Logs the current context's specifications.
///
static void LogContextSpecifications() noexcept;

void OnBeginRun() noexcept
{
    Window::ShowWindow(sWindow);
    Window::SetWindowResizable(sWindow, false);

    LogContextSpecifications();

    gl::UseProgram(sPaddleProgram);
}

#define LEPONG_LOG_GL_STRING(name) \
    Log::Log(reinterpret_cast<const char*>(gl::GetString(gl::name)))

void LogContextSpecifications() noexcept
{
    LEPONG_LOG_GL_STRING(Version);
    LEPONG_LOG_GL_STRING(Vendor);
    LEPONG_LOG_GL_STRING(Renderer);
}

void OnUpdate() noexcept
{
    sRunning = Window::PollEvents();
}

///
/// Loads the required uniforms and draws a quad.
///
static void DrawQuad(const Vector2f& size, const Vector2f& position, GLuint program) noexcept;

void OnRender() noexcept
{
    gl::Clear(gl::ColorBufferBit);

    DrawQuad(Vector2f{ 20, 150 }, sPaddlePosition, sPaddleProgram);
    gl::SwapBuffers(sContext);
}

void DrawQuad(const Vector2f& size, const Vector2f& position, GLuint program) noexcept
{
    gl::UseProgram(program);

    const auto kSizeLocation = gl::GetUniformLocation(program, "uSize");
    const auto kPositionLocation = gl::GetUniformLocation(program, "uPosition");

    gl::Uniform2f(kSizeLocation, size.x, size.y);
    gl::Uniform2f(kPositionLocation, position.x, position.y);

    Graphics::DrawMesh(sQuad);
}

void OnFinishRun() noexcept
{
    Window::HideWindow(sWindow);
}

void Cleanup() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sInitialized && !sRunning);

    CleanupItems(kGameLifetimes);
    sInitialized = false;
}

} // namespace lepong
