//
// Created by lepouki on 10/12/2020.
//

#include <cstdint>

#include "lepong/Assert.h"
#include "lepong/Attribute.h"
#include "lepong/Window.h"

#include "lepong/Graphics/Graphics.h"

namespace lepong
{

static auto sInitialized = false;
static HWND sWindow = nullptr;

///
/// Initializes the game's systems.
///
LEPONG_NODISCARD static bool InitGameSystems() noexcept;

///
/// Initializes the game's state and resources.
///
LEPONG_NODISCARD static bool InitState() noexcept;

///
/// Cleans up the game's systems.<br>
/// This documentation is very useful yes.
///
static void CleanupSystems() noexcept;

bool Init() noexcept
{
    if (sInitialized)
    {
        return false;
    }

    if (InitGameSystems())
    {
        if (InitState())
        {
            sInitialized = true;
        }
        else
        {
            CleanupSystems();
        }
    }

    return sInitialized;
}

///
/// A struct holding the init and cleanup functions of an item.<br>
/// This item could be anything as long as its init and cleanup functions use the correct signatures.
///
struct ItemLifetime
{
public:
    ///
    /// A generic initialization function.
    ///
    using PFNInit = bool (*)();

    ///
    /// A generic cleanup function.
    ///
    using PFNCleanup = void (*)();

public:
    PFNInit init;
    PFNCleanup cleanup;

public:
    ///
    /// Both init and cleanup functions must be provided.
    ///
    constexpr ItemLifetime(PFNInit init, PFNCleanup cleanup) noexcept
        : init(init)
        , cleanup(cleanup)
    {
        LEPONG_ASSERT(init, "init must not be nullptr");
        LEPONG_ASSERT(cleanup, "cleanup must not be nullptr");
    }
};

///
/// All the system lifetimes.<br>
/// A system has to be declared after all the systems it depends on.
///
static constexpr ItemLifetime kSystemLifetimes[] =
{
    { Window::Init, Window::Cleanup },
    { Graphics::Init, Graphics::Cleanup }
};

///
/// A wrapper for the pretty ugly array reference syntax.
///
template<typename T, std::size_t Size>
using ConstArrayReference = const T (&)[Size];

///
/// Tries to run all the provided lifetime initialization functions.<br>
/// If an initialization function fails, the cleanup functions of the initialized items are called.
///
/// \return Whether all the items have been successfully initialized.
///
template<std::size_t NumItems>
LEPONG_NODISCARD static bool TryInitItems(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes) noexcept;

bool InitGameSystems() noexcept
{
    return TryInitItems(kSystemLifetimes);
}

///
/// Cleans up all the items starting from the item at the provided index.<br>
/// Items are cleaned up in reverse order.
///
/// \param index The index of the first system to cleanup.
///
template<std::size_t NumItems>
static void CleanupItemsStartingAt(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes, unsigned index) noexcept;

template<std::size_t NumItems>
bool TryInitItems(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes) noexcept
{
    auto succeeded = true;

    for (unsigned i = 0; succeeded && i < NumItems; ++i)
    {
        succeeded = itemLifetimes[i].init();

        if (!succeeded)
        {
            CleanupItemsStartingAt(itemLifetimes, i);
        }
    }

    return succeeded;
}

template<std::size_t NumItems>
void CleanupItemsStartingAt(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes, unsigned index) noexcept
{
    for (auto i = static_cast<int>(index) - 1; i >= 0; --i)
    {
        itemLifetimes[i].cleanup();
    }
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
/// Contains the lifetimes of all the game state items.
///
static constexpr ItemLifetime kStateLifetimes[] =
{
    { InitWindow, CleanupWindow }
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

void CleanupWindow() noexcept
{
    Window::DestroyWindow(sWindow);
}

void OnKeyEvent(int key, bool pressed) noexcept
{
    (void)key;
    (void)pressed;
}

///
/// Calls the cleanup function of all the provided item lifetimes.
///
template<std::size_t NumItems>
static void CleanupItems(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes) noexcept;

void CleanupSystems() noexcept
{
    CleanupItems(kSystemLifetimes);
}

template<std::size_t NumItems>
void CleanupItems(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes) noexcept
{
    CleanupItemsStartingAt(itemLifetimes, NumItems);
}

static auto sRunning = false;

///
/// \return Whether the game should keep running.
///
LEPONG_NODISCARD static bool PollEvents() noexcept;

void Run() noexcept
{
    if (sRunning || !sInitialized)
    {
        return;
    }

    sRunning = true;

    ShowWindow(sWindow, SW_SHOW);
    Window::SetWindowResizable(sWindow, false);

    while (sRunning)
    {
        sRunning = PollEvents();
    }

    ShowWindow(sWindow, SW_HIDE);
}

///
/// Dispatches the provided message to the event callback.
///
static void Dispatch(const MSG& msg) noexcept;

bool PollEvents() noexcept
{
    MSG msg = {};
    auto keepRunning = true;

    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        Dispatch(msg);
        keepRunning &= (msg.message != WM_QUIT);
    }

    return keepRunning;
}

void Dispatch(const MSG& msg) noexcept
{
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
}

///
/// Cleans up the game's state and resources.
///
static void CleanupState() noexcept;

void Cleanup() noexcept
{
    if (sInitialized && !sRunning)
    {
        // Order is important
        CleanupState();
        CleanupSystems();

        sInitialized = false;
    }
}

void CleanupState() noexcept
{
    CleanupItems(kStateLifetimes);
}

} // namespace lepong
