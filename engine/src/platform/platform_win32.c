#include "platform/platform.h"

#ifdef MPLATFORM_WINDOWS

#include <windows.h>
#include <windowsx.h>
#include <wincon.h>
#include <stdlib.h>

#include "utils/logger.h"

typedef struct Win32_State {
    HINSTANCE module_instance_handle;
    HWND window_handle;
} Win32_State;

global f64 clock_frequency;
global LARGE_INTEGER start_time;

LRESULT CALLBACK win32_process_message(HWND window_handle, u32 message, WPARAM w_param, LPARAM l_param);

b8 platform_start(Platform* platform, const char* name, i32 x, i32 y, i32 width, i32 height) {
    platform->state = malloc(sizeof(Win32_State));
    Win32_State* win32_state = (Win32_State*) platform->state;

    win32_state->module_instance_handle = GetModuleHandleA(0);

    // NOTE: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassa
    WNDCLASSA window_class;
    memset(&window_class, 0, sizeof(window_class));
    window_class.hIcon = LoadIcon(win32_state->module_instance_handle, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(0, IDC_ARROW);
    window_class.hInstance = win32_state->module_instance_handle;
    window_class.style = CS_DBLCLKS;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hbrBackground = 0;
    window_class.lpszClassName = "marionette_window";
    window_class.lpfnWndProc = win32_process_message;

    if (!RegisterClassA(&window_class)) {
        MessageBoxA(0, "failed to register window class", "Fatal error", MB_ICONEXCLAMATION | MB_OK);
        FATAL("failed to register window class");
        return false;
    }

    u32 client_x = x;
    u32 client_y = y;
    u32 client_width = width;
    u32 client_height = height;

    u32 window_x = client_x;
    u32 window_y = client_y;
    u32 window_width = client_width;
    u32 window_height = client_height;

    u32 window_styles = WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME;
    u32 window_ex_styles = WS_EX_APPWINDOW;

    RECT window_rect = { 0, 0, 0, 0 };
    AdjustWindowRectEx(&window_rect, window_styles, 0, window_ex_styles);

    window_x += window_rect.left;
    window_y += window_rect.top;

    window_width += window_rect.right - window_rect.left;
    window_height += window_rect.top - window_rect.bottom;

    // NOTE: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa
    HWND window_handle = CreateWindowExA(
        window_ex_styles, window_class.lpszClassName, name, 
        window_styles, window_x, window_y, window_width, window_height, 
        0, 0, win32_state->module_instance_handle, 0
    );

    if (!window_handle) {
        MessageBoxA(0, "failed to create window", "Fatal error", MB_ICONEXCLAMATION | MB_OK);
        FATAL("failed to create window class");
        return false;
    }

    win32_state->window_handle = window_handle;

    // NOTE: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
    ShowWindow(win32_state->window_handle, SW_SHOW);

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (f64) frequency.QuadPart;

    QueryPerformanceCounter(&start_time);

    return true;
}

b8 platform_stop(Platform* platform) {
    Win32_State* win32_state = (Win32_State*) platform->state;
    
    if (win32_state->window_handle) {
        if (!DestroyWindow(win32_state->window_handle)) {
            return false;
        }
        win32_state->window_handle = 0;
    }

    return true;
}

b8 platform_pull_messages(Platform* platform) {
    MSG message;

    // NOTE: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea
    while(PeekMessageA(&message, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return true;
}

void* platform_allocate(u64 size, b8 _is_aligned) {
    return malloc(size);
}

void platform_free(void* block, b8 _is_aligned) {
    free(block);
}

void* platform_zero_memory(void* block, u64 size) {
    return memset(block, 0, size);
}

void* platform_copy_memory(void* destination, const void* source, u64 size) {
    return memcpy(destination, source, size);
}

void* platform_set_memory(void* block, i32 value, u64 size) {
    return memset(block, value, size);
}

void platform_print(const char* message, u8 level) {
    OutputDebugStringA(message); 
    
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // NOTE: https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#span-idwin32characterattributesspanspan-idwin32characterattributesspancharacter-attributes
    local u8 levels[6] = {
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY, 
        FOREGROUND_RED | FOREGROUND_INTENSITY, 
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        FOREGROUND_GREEN | FOREGROUND_INTENSITY, 
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, 
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    };
    SetConsoleTextAttribute(console_handle, levels[level]);

    u64 size = strlen(message);
    LPDWORD bytes_written = 0;
    WriteConsoleA(console_handle, message, (DWORD)size, bytes_written, 0);
}

void platform_printerr(const char* message, u8 level) {
    OutputDebugStringA(message); 
    
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    
    // NOTE: https://learn.microsoft.com/en-us/windows/console/console-screen-buffers#span-idwin32characterattributesspanspan-idwin32characterattributesspancharacter-attributes
    local u8 levels[6] = {
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY, 
        FOREGROUND_RED | FOREGROUND_INTENSITY, 
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        FOREGROUND_GREEN | FOREGROUND_INTENSITY, 
        FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, 
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    };
    SetConsoleTextAttribute(console_handle, levels[level]);

    u64 size = strlen(message);
    LPDWORD bytes_written = 0;
    WriteConsoleA(console_handle, message, (DWORD)size, bytes_written, 0);
}

f64 platform_current_time() {
    // NOTE: http://learn.microsoft.com/en-us/windows/win32/sysinfo/acquiring-high-resolution-time-stamps
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);
    return (f64) current_time.QuadPart * clock_frequency;
}

void platform_sleep(u64 delay_ms) {
    Sleep(delay_ms);
}

LRESULT CALLBACK win32_process_message(HWND window_handle, u32 message, WPARAM w_param, LPARAM l_param) {
    // NOTE: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-callwindowprocw
    switch(message) {
        case WM_ERASEBKGND:
            return 1;
        case WM_CLOSE:
            // TODO: dipatch that event stop the game loop
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE: {
            // TODO: dispatch the new size to resize the window
        } break;
        case WM_KEYUP:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN: {
            // TODO: process keyboard events 
        } break;
        case WM_MOUSEMOVE: {
            // TODO: process mouse move
        } break;
        case WM_MOUSEHWHEEL: {
            // TODO: process mouse wheel delta
        } break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP: {
            // TODO: process mouse button click
        } break;
    }

    // NOTE: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-defwindowprocw
    return DefWindowProcA(window_handle, message, w_param, l_param);
}

#endif