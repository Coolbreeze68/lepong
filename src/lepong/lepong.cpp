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
static Graphics::GL::Context sContext;

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
        : mInit(init)
        , mCleanup(cleanup)
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
    { Graphics::GL::Init, Graphics::GL::Cleanup }
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
LEPONG_NODISCARD static bool InitWindow() noexcept;

///
/// Cleans up the game window.
///
static void CleanupWindow() noexcept;

///
/// \return Whether the rendering context was successfully initialized.
///
LEPONG_NODISCARD static bool InitContext() noexcept;

///
/// Cleans up the rendering context.
///
static void CleanupContext() noexcept;

///
/// All the game state lifetimes.
///
static constexpr Lifetime kStateLifetimes[] =
{
    { InitWindow, CleanupWindow },
    { InitContext, CleanupContext }
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

bool InitWindow() noexcept
{
    Window::SetKeyCallback(OnKeyEvent);
    sWindow = Window::MakeWindow(Vector2i{ 1280, 720 }, L"lepong");
    return sWindow;
}

void OnKeyEvent(int key, bool pressed) noexcept
{
    (void)key;
    (void)pressed;
}

void CleanupWindow() noexcept
{
    Window::DestroyWindow(sWindow);
}

bool InitContext() noexcept
{
    sContext = Graphics::GL::MakeContext(sWindow);
    return sContext.context;
}

void CleanupContext() noexcept
{
    Graphics::GL::DestroyContext(sContext);
}

void CleanupState() noexcept
{
    CleanupItems(kStateLifetimes);
}

static auto sRunning = false;

///
/// Logs the current context's specifications.
///
static void LogContextSpecifications() noexcept;

void Run() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sInitialized && !sRunning);

    sRunning = true;

    Window::ShowWindow(sWindow);
    Window::SetWindowResizable(sWindow, false);

    Graphics::GL::MakeContextCurrent(sContext);
    LogContextSpecifications();

    while (sRunning)
    {
        sRunning = Window::PollEvents();
    }

    Window::HideWindow(sWindow);
}

#define LEPONG_LOG_GL_STRING(name) \
    Log::Log(reinterpret_cast<const char*>(glGetString(name)))

void LogContextSpecifications() noexcept
{
    LEPONG_LOG_GL_STRING(GL_VERSION);
    LEPONG_LOG_GL_STRING(GL_VENDOR);
    LEPONG_LOG_GL_STRING(GL_RENDERER);
}

void Cleanup() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sInitialized && !sRunning);

    CleanupItems(kGameLifetimes);
    sInitialized = false;
}

} // namespace lepong
