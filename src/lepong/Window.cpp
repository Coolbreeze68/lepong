//
// Created by lepouki on 10/12/2020.
//

#include "lepong/Assert.h"
#include "lepong/Window.h"

namespace lepong::Window
{

static auto sInitialized = false;
static auto sModule = GetModuleHandleW(nullptr); // NOLINT: Clang-Tidy thinks GetModuleHandleW can throw.

///
/// Registers the window class used to create the game's window.
///
static bool RegisterWindowClass(WNDPROC callback) noexcept;

bool Init(WNDPROC callback) noexcept
{
    if (sInitialized)
    {
        return false;
    }

    LEPONG_ASSERT(callback, "callback can't be nullptr");
    sInitialized = RegisterWindowClass(callback);
    return sInitialized;
}

static constexpr auto skClassName = L"lepongWindow";

static bool RegisterWindowClass(WNDPROC callback) noexcept
{
    WNDCLASSW windowClass = {};
    windowClass.lpfnWndProc = callback;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpszClassName = skClassName;
    windowClass.hInstance = sModule;
    return RegisterClassW(&windowClass);
}

void Cleanup() noexcept
{
    if (sInitialized)
    {
        UnregisterClassW(skClassName, sModule);
        sInitialized = false;
    }
}

HWND MakeWindow(const Vector2i& size, const wchar_t* title) noexcept
{
    if (!sInitialized)
    {
        return nullptr;
    }

    return CreateWindowExW(
        WS_EX_APPWINDOW,
        skClassName,
        title,
        WS_OVERLAPPEDWINDOW, // NOLINT: Clang-Tidy needs to chill the FUCK down.
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        nullptr,
        sModule,
        nullptr);
}

void DestroyWindow(HWND window) noexcept
{
    LEPONG_ASSERT(window, "window can't be nullptr");
    ::DestroyWindow(window);
}

} // namespace lepong::Window
