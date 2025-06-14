#include "platform.h"

#ifdef _WIN32

#include "engine.h"
#include "app_config.h"
#include "windows_renderer.h"
#include "time.h"
#include <stdio.h>
#include <windows.h>


static HWND hwnd = NULL;


// Windows Message Callback
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE: DestroyWindow(hwnd); return 0;
        case WM_DESTROY: PostQuitMessage(0); return 0;
        case WM_SIZE: {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);

            if (engine_is_running()) {
                appconfig_platform_resized_window_px(width, height);
            }

            return 0;
        }
        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void platform_start() {
    struct ApplicationConfig* config = appconfig_get();

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "WindowClass";

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, "WindowClass", config->window_name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        config->window_aspect.width, config->window_aspect.height,
        NULL, NULL, wc.hInstance, NULL
    );

    if (!hwnd) {
        printf("HWND is Null... exiting\n");
        return;
    }

    ShowWindow(hwnd, SW_SHOW);
    initialize_time_frequency();
    engine_start(create_windows_renderer(&hwnd));

    MSG msg = {0};
    while (1) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT || !engine_is_running()) {
                printf("...Closing Properly...\n");
                engine_close();
                return;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        engine_tick();
        Sleep(1); // TODO: Look into adjusting this
    }

    engine_close();
}

void platform_resize_window(struct Aspect* windowSize) {
    SetWindowPos(hwnd, NULL, 0, 0, windowSize->width, windowSize->height, SWP_NOMOVE | SWP_NOZORDER);
}

void platform_name_window(const char* name) {
    SetWindowText(hwnd, name);
}


#else
// ToDo: Unix

#endif