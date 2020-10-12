//
// Created by lepouki on 10/12/2020.
//

#include "lepong/Assert.h"
#include "lepong/Window.h"

namespace lepong::Window
{

static auto sInitialized = false;

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

#define LEPONG_THIS_MODULE GetModuleHandleW(nullptr)

static constexpr auto skClassName = L"lepongWindow";

static bool RegisterWindowClass(WNDPROC callback) noexcept
{
    WNDCLASSW windowClass = {};
    windowClass.lpszClassName = skClassName;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpfnWndProc = callback;
    windowClass.hInstance = LEPONG_THIS_MODULE;
    return RegisterClassW(&windowClass);
}

void Cleanup() noexcept
{
    if (sInitialized)
    {
        UnregisterClassW(skClassName, LEPONG_THIS_MODULE);
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
        LEPONG_THIS_MODULE,
        nullptr);
}

void DestroyWindow(HWND window) noexcept
{
    LEPONG_ASSERT(window, "window can't be nullptr");
    ::DestroyWindow(window);
}

} // namespace lepong::Window
