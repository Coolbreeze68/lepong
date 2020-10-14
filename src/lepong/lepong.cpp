//
// Created by lepouki on 10/12/2020.
//

#include <cstdint>

#include "lepong/Assert.h"
#include "lepong/Attribute.h"
#include "lepong/Log.h"
#include "lepong/Window.h"

#include "lepong/Graphics/Graphics.h"

namespace lepong
{

static auto sInitialized = false;
static HWND sWindow;

///
/// A class holding the init and cleanup functions of an item.<br>
/// The item could be anything as long as its init and cleanup functions use the correct signatures.
///
struct ItemLifetime
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
    constexpr ItemLifetime(PFNInit init, PFNCleanup cleanup) noexcept
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
static constexpr ItemLifetime kGameLifetimes[] =
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
LEPONG_NODISCARD static bool TryInitItems(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes) noexcept;

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
static void CleanupItemsStartingAt(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes, unsigned index) noexcept;

template<std::size_t NumItems>
bool TryInitItems(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes) noexcept
{
    auto succeeded = true;

    for (unsigned i = 0; succeeded && i < NumItems; ++i)
    {
        succeeded = itemLifetimes[i].Init();

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
        itemLifetimes[i].Cleanup();
    }
}

///
/// All the system lifetimes.<br>
/// A system has to be declared after all the systems it depends on.
///
static constexpr ItemLifetime kSystemLifetimes[] =
{
    { Window::Init, Window::Cleanup },
    { Log::Init, Log::Cleanup },
    { Graphics::Init, Graphics::Cleanup }
};

bool InitGameSystems() noexcept
{
    return TryInitItems(kSystemLifetimes);
}

///
/// Calls the cleanup function of all the provided item lifetimes.
///
template<std::size_t NumItems>
static void CleanupItems(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes) noexcept;

void CleanupGameSystems() noexcept
{
    CleanupItems(kSystemLifetimes);
}

template<std::size_t NumItems>
void CleanupItems(ConstArrayReference<ItemLifetime, NumItems> itemLifetimes) noexcept
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

void OnKeyEvent(int key, bool pressed) noexcept
{
    (void)key;
    (void)pressed;
}

void CleanupWindow() noexcept
{
    Window::DestroyWindow(sWindow);
}

void CleanupState() noexcept
{
    CleanupItems(kStateLifetimes);
}

static auto sRunning = false;

void Run() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sInitialized && !sRunning);

    sRunning = true;

    Window::ShowWindow(sWindow);
    Window::SetWindowResizable(sWindow, false);

    while (sRunning)
    {
        sRunning = Window::PollEvents();
    }

    Window::HideWindow(sWindow);
}

void Cleanup() noexcept
{
    LEPONG_ASSERT_OR_RETURN(sInitialized && !sRunning);

    CleanupItems(kGameLifetimes);
    sInitialized = false;
}

} // namespace lepong
