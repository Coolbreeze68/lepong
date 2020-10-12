//
// Created by lepouki on 10/12/2020.
//

#include <iostream> // Debug

#include "lepong/Window.h"

namespace lepong
{

static auto sInitialized = false;
static HWND sWindow = nullptr;

///
/// The game's main event callback.
///
static LRESULT CALLBACK EventCallback(HWND, UINT, WPARAM, LPARAM) noexcept;

///
/// Initializes the game's systems.
///
/// \param callback The game's event callback.
///
static bool InitSystems(WNDPROC callback) noexcept;

///
/// Initializes the game's state and resources.
///
static bool InitState() noexcept;

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

    if (InitSystems(EventCallback))
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
/// \param key The pressed key's virtual key code.
///
static void OnKeyPressed(int key) noexcept;

///
/// \param key The released key's virtual key code.
///
static void OnKeyReleased(int key) noexcept;

LRESULT CALLBACK EventCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (message)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
    {
        // This is true if the key was up before the WM_KEYDOWN message.
        const auto kJustPressed = !(static_cast<ULONG_PTR>(lParam) & 0x40000000u);

        if (kJustPressed)
        {
            OnKeyPressed(wParam);
        }

        return 0;
    }

    case WM_KEYUP:
        OnKeyReleased(wParam);
        return 0;

    default:
        break;
    }

    return DefWindowProcW(window, message, wParam, lParam);
}

void OnKeyPressed(int key) noexcept
{
    std::cout << key << std::endl;
}

void OnKeyReleased(int key) noexcept
{
    std::cout << key << std::endl;
}

bool InitSystems(WNDPROC callback) noexcept
{
    return Window::Init(callback);
}

bool InitState() noexcept
{
    sWindow = Window::MakeWindow(Vector2i{ 1280, 720 }, L"lepong");
    return sWindow;
}

void CleanupSystems() noexcept
{
    Window::Cleanup();
}

static auto sRunning = false;

///
/// \return Whether the game should keep running.
///
static bool PollEvents() noexcept;

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
}

///
/// Dispatches the provided message to the event callback.
///
static void Dispatch(const MSG& msg) noexcept;

static bool PollEvents() noexcept
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
    Window::DestroyWindow(sWindow);
}

} // namespace lepong
