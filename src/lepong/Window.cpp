//
// Created by lepouki on 10/12/2020.
//

#include "lepong/Assert.h"
#include "lepong/Attribute.h"
#include "lepong/Window.h"

namespace lepong::Window
{

static auto sInitialized = false;
static auto sModule = GetModuleHandleW(nullptr); // NOLINT: Clang-Tidy thinks GetModuleHandleW can throw.

///
/// Registers the window class used to create the game's window.
///
LEPONG_NODISCARD static bool RegisterWindowClass() noexcept;

bool Init() noexcept
{
    if (sInitialized)
    {
        return false;
    }

    sInitialized = RegisterWindowClass();
    return sInitialized;
}

///
/// The function called everytime a message is sent to the window.
///
static LRESULT CALLBACK OnMessage(HWND, UINT, WPARAM, LPARAM) noexcept;

static constexpr auto skClassName = L"lepongWindow";

static bool RegisterWindowClass() noexcept
{
    WNDCLASSW windowClass = {};
    windowClass.lpfnWndProc = OnMessage;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpszClassName = skClassName;
    windowClass.hInstance = sModule;
    return RegisterClassW(&windowClass);
}

static PFNKeyCallback sKeyCallback = nullptr;

LRESULT CALLBACK OnMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (message)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        // ^ This assumes there will always be a single window.
        return 0;

    case WM_KEYDOWN:
    {
        const bool kHeld = static_cast<ULONG_PTR>(lParam) & 0x40000000u;

        if (kHeld)
        {
            // Ignore the message if the key is held down.
            break;
        }

        LEPONG_FALLTHROUGH;
    }

    case WM_KEYUP:
    {
        if (sKeyCallback)
        {
            sKeyCallback(wParam, message == WM_KEYDOWN);
            return 0;
        }

        break;
    }

    default: break;
    }

    return DefWindowProcW(window, message, wParam, lParam);
}

void SetKeyCallback(PFNKeyCallback callback) noexcept
{
    sKeyCallback = callback;
}

void Cleanup() noexcept
{
    if (sInitialized)
    {
        UnregisterClassW(skClassName, sModule);
        sInitialized = false;
    }
}

///
/// Calculates the dimensions of the client area based on the provided size.<br>
/// The resulting client area is centered on the screen.
///
LEPONG_NODISCARD static RECT CenterClientArea(const Vector2i& size) noexcept;

HWND MakeWindow(const Vector2i& size, const wchar_t* title) noexcept
{
    if (!sInitialized)
    {
        return nullptr;
    }

    const auto kArea = CenterClientArea(size);

    const Vector2i kSize =
    {
        static_cast<int>(kArea.right - kArea.left),
        static_cast<int>(kArea.bottom - kArea.top)
    };

    return CreateWindowExW(
        WS_EX_APPWINDOW,
        skClassName, title,
        WS_OVERLAPPEDWINDOW, // NOLINT: Clang-Tidy needs to chill the FUCK down.
        kArea.left, kArea.top,
        kSize.x, kSize.y,
        nullptr, nullptr,
        sModule, nullptr);
}

///
/// Adjusts the area size so that the client area is as big as the provided size.
///
LEPONG_NODISCARD static Vector2i AdjustAreaSize(const Vector2i& size) noexcept;

RECT CenterClientArea(const Vector2i& size) noexcept
{
    const Vector2i kScreenHalfSize =
    {
        GetSystemMetrics(SM_CXSCREEN) / 2,
        GetSystemMetrics(SM_CYSCREEN) / 2
    };

    const auto kAreaHalfSize = AdjustAreaSize(size) / 2;

    return
    {
        kScreenHalfSize.x - kAreaHalfSize.x, // left
        kScreenHalfSize.y - kAreaHalfSize.y, // top
        kScreenHalfSize.x + kAreaHalfSize.x, // right
        kScreenHalfSize.y + kAreaHalfSize.y  // bottom
    };
}

Vector2i AdjustAreaSize(const Vector2i& size) noexcept
{
    RECT areaRect =
    {
        0, 0,
        size.x, size.y
    };

    AdjustWindowRectEx(
        &areaRect,
        WS_OVERLAPPEDWINDOW, // NOLINT: Shut up Clang-Tidy.
        FALSE,
        WS_EX_APPWINDOW);

    return
    {
        static_cast<int>(areaRect.right), // left and top are 0.
        static_cast<int>(areaRect.bottom) // ^
    };
}

void DestroyWindow(HWND window) noexcept
{
    LEPONG_ASSERT(window, "window can't be nullptr");
    ::DestroyWindow(window);
}

///
/// Sets the provided window's style to the provided style.
///
static void SetWindowStyle(HWND window, DWORD style) noexcept;

///
/// \return The provided window's style. Who could have guessed?
///
LEPONG_NODISCARD static DWORD GetWindowStyle(HWND window) noexcept;

void SetWindowResizable(HWND window, bool resizable) noexcept
{
    constexpr DWORD kResizableStyle = WS_MAXIMIZEBOX | WS_THICKFRAME; // NOLINT: PLEASE STOP.
    const auto kStyle = GetWindowStyle(window);

    SetWindowStyle(window,
        resizable
           ? kStyle | kResizableStyle
           : kStyle ^ kResizableStyle);
}

void SetWindowStyle(HWND window, DWORD style) noexcept
{
    SetWindowLongW(window, GWL_STYLE, style);
}

DWORD GetWindowStyle(HWND window) noexcept
{
    return GetWindowLongW(window, GWL_STYLE);
}

} // namespace lepong::Window
