//
// Created by lepouki on 10/12/2020.
//

#include <cstdint>

#include "lepong/Assert.h"
#include "lepong/Attribute.h"
#include "lepong/lepong.h"
#include "lepong/Log.h"
#include "lepong/Window.h"

#include "lepong/Graphics/Graphics.h"

namespace lepong
{

static auto sInitialized = false;

static HWND sWindow;
static gl::Context sContext;

static GLuint sTriangleProgram;
static GLuint sTriangleVB;

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
    { Window::Init, Window::Cleanup },
    { Log::Init, Log::Cleanup },
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
    sWindow = Window::MakeWindow(Vector2i{1280, 720}, L"lepong");
    return sWindow;
}

void OnKeyEvent(LEPONG_MAYBE_UNUSED int key, LEPONG_MAYBE_UNUSED bool pressed) noexcept
{
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
LEPONG_NODISCARD static bool InitTriangleProgram() noexcept;

///
/// You guessed it.
///
static void CleanupTriangleProgram() noexcept;

///
/// \return I think you can guess.
///
LEPONG_NODISCARD static bool InitTriangleVB() noexcept;

///
/// You guessed it again.
///
static void CleanupTriangleVB() noexcept;

///
/// All the graphics resource lifetimes.
///
static constexpr Lifetime kGraphicsResourceLifetimes[] =
{
    { InitTriangleProgram, CleanupTriangleProgram },
    { InitTriangleVB, CleanupTriangleVB }
};

bool InitGraphicsResources() noexcept
{
    return TryInitItems(kGraphicsResourceLifetimes);
}

///
/// \return The triangle vertex shader.
///
static GLuint CreateTriangleVertShader() noexcept;

///
/// \return The triangle fragment shader. Unbelievable.
///
static GLuint CreateTriangleFragShader() noexcept;

bool InitTriangleProgram() noexcept
{
    const auto kVert = CreateTriangleVertShader();
    const auto kFrag = CreateTriangleFragShader();

    sTriangleProgram = Graphics::CreateProgramFromShaders(kVert, kFrag);

    gl::DeleteShader(kVert);
    gl::DeleteShader(kFrag);

    return sTriangleProgram;
}

GLuint CreateTriangleVertShader() noexcept
{
    constexpr auto kSource =
    R"(

    #version 330 core

    layout (location = 0) in vec2 aPosition;
    layout (location = 1) in vec3 aColor;

    out vec3 vColor;

    void main()
    {
        gl_Position = vec4(aPosition, 0.0, 1.0);
        vColor = aColor;
    }

    )";

    return Graphics::CreateShaderFromSource(gl::VertexShader, kSource);
}

GLuint CreateTriangleFragShader() noexcept
{
    constexpr auto kSource =
    R"(

    #version 330 core

    in vec3 vColor;

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(vColor, 1.0);
    }

    )";

    return Graphics::CreateShaderFromSource(gl::FragmentShader, kSource);
}

void CleanupTriangleProgram() noexcept
{
    gl::DeleteProgram(sTriangleProgram);
}

///
/// Sends triangle data to the triangle vertex shader.
///
static void InitTriangleVertexData() noexcept;

bool InitTriangleVB() noexcept
{
    gl::GenBuffers(1, &sTriangleVB);

    if (sTriangleVB)
    {
        InitTriangleVertexData();
    }

    return sTriangleVB;
}

void InitTriangleVertexData() noexcept
{
    gl::BindBuffer(gl::ArrayBuffer, sTriangleVB);

    constexpr GLfloat kVertices[] =
    {
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 1.0f, 0.0f, 1.0f
    };

    gl::BufferData(gl::ArrayBuffer, sizeof(kVertices), kVertices, gl::StaticDraw);

    const auto kStride = sizeof(GLfloat) * 5;

    gl::EnableVertexAttribArray(0);
    gl::VertexAttribPointer(0, 2, gl::Float, gl::False, kStride, nullptr);

    const auto kOffset = reinterpret_cast<void*>(sizeof(GLfloat) * 2);

    gl::EnableVertexAttribArray(1);
    gl::VertexAttribPointer(1, 3, gl::Float, gl::False, kStride, kOffset);
}

void CleanupTriangleVB() noexcept
{
    gl::DeleteBuffers(1, &sTriangleVB);
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

    gl::UseProgram(sTriangleProgram);
}

#define LEPONG_LOG_GL_STRING(name) \
    Log::Log(reinterpret_cast<const char*>(gl::GetString(name)))

void LogContextSpecifications() noexcept
{
    LEPONG_LOG_GL_STRING(gl::Version);
    LEPONG_LOG_GL_STRING(gl::Vendor);
    LEPONG_LOG_GL_STRING(gl::Renderer);
}

void OnUpdate() noexcept
{
    sRunning = Window::PollEvents();
}

void OnRender() noexcept
{
    gl::DrawArrays(gl::Triangles, 0, 3);
    gl::SwapBuffers(sContext);
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
