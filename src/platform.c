#include "platform.h"
#include "engine.h"
#include "app_config.h"
#include <stdio.h>
#include "time.h"


#ifdef _WIN32

#include "windows_renderer.h"
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

#include <xcb/xcb.h>


void platform_start() {
	xcb_connection_t* connection = xcb_connection(NULL, NULL);
	if (xcb_connection_has_error(connection)) {
		printf("Failed to connect to X Server\n");
		return;
	}

	const xcb_setup_t* setup = xcb_get_setup(connection);
	xcb_screen_interator_t iter = xcb_setup_roots_iterator(setup);
	xcb_screen_t* screen = iter.data;

    xcb_window_t window = xcb_generate_id(connection);
    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t values[2] = {
        screen->black_pixel,
        XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS
    };

    xcb_create_window(
        connection, XCB_COPY_FROM_PARENT, window, screen->root,
        100, 100, 800, 600, 0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual,
        mask, values
    );

    xcb_change_property(
        connection, XCB_PROP_MODE_REPLACE, window,
        XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
        strlen("Hello XCB"), "Hello XCB"
    );

    xcb_map_window(connection, window);
    xcb_flush(connection);

    xcb_generic_event_t *event;
    // while ((event = xcb_wait_for_event(connection))) {
    //     switch (event->response_type & ~0x80) {
    //         case XCB_EXPOSE:
    //             printf("Expose event\n");
    //             break;
    //         case XCB_KEY_PRESS:
    //             printf("Key pressed, exiting...\n");
    //             free(event);
    //             goto end;
    //     }
    //     free(event);
    // }
}


#endif
