#include "platform.h"
#include "engine.h"
#include "app_config.h"
#include <stdio.h>
#include <xcb/xproto.h>
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
// TODO: Unix

#include <xcb/xcb.h>
#include <stdlib.h>
#include <string.h>

static xcb_connection_t* connection = NULL;
static xcb_window_t window;

void platform_start() {
    struct ApplicationConfig* config = appconfig_get();

    // Connect to the X server
    connection = xcb_connect(NULL, NULL);
    if (xcb_connection_has_error(connection)) {
        printf("Failed to connect to X Server\n");
        return;
    }

    const xcb_setup_t* setup = xcb_get_setup(connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t* screen = iter.data;

    window = xcb_generate_id(connection);

    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t values[2] = {
        screen->black_pixel,
        XCB_EVENT_MASK_EXPOSURE |
        XCB_EVENT_MASK_KEY_PRESS |
        XCB_EVENT_MASK_STRUCTURE_NOTIFY // for resize
    };

    xcb_create_window(
        connection,
        XCB_COPY_FROM_PARENT,
        window,
        screen->root,
        100, 100,
        config->window_aspect.width,
        config->window_aspect.height,
        0,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        screen->root_visual,
        mask, values
    );

    // Set the window name, dont use platform_name_window, since it flushes
    xcb_change_property(
        connection,
        XCB_PROP_MODE_REPLACE,
        window,
        XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING,
        8,
        strlen(config->window_name),
        config->window_name
    );

    xcb_map_window(connection, window);
    
    // Setup listener for WM_DELETE_WINDOW
    // TODO: Theres got to be a more optimal way to do this part
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");
    xcb_intern_atom_reply_t* reply = xcb_intern_atom_reply(connection, cookie, NULL); // THIS FLUSHES ALL PREV REQUESTS
    xcb_atom_t wm_protocols = reply->atom;
    free(reply);
    cookie = xcb_intern_atom(connection, 0, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW");
    reply = xcb_intern_atom_reply(connection, cookie, NULL);
    xcb_atom_t wm_delete_window = reply->atom;
    free(reply);
    
    // Now an atom will be sent instead of the App dying when user hits X
    xcb_change_property(
        connection,
        XCB_PROP_MODE_REPLACE,
        window,
        wm_protocols,
        4, 32, 1, &wm_delete_window
    );

    xcb_flush(connection);

    // Initialize renderer and engine
    // engine_start(create_unix_renderer(connection, &window));

    // Event / Engine loop
    while (engine_is_running()) {
        xcb_generic_event_t *event;
        while ((event = xcb_poll_for_event(connection))) {
            switch (event->response_type & ~0x80) {
                case XCB_EXPOSE:
                    // Could trigger a redraw
                    break;
                case XCB_CONFIGURE_NOTIFY: {
                    // Window resized
                    xcb_configure_notify_event_t* cfg = (xcb_configure_notify_event_t*)event;
                    appconfig_platform_resized_window_px(cfg->width, cfg->height);
                    break;
                }
                case XCB_CLIENT_MESSAGE: {
                    xcb_client_message_event_t* cm = (xcb_client_message_event_t*) event;
                    if (cm->data.data32[0] == wm_delete_window) {
                        printf("User clicked X, closing window..\n");
                        goto end;
                    }
                }
                // case XCB_KEY_PRESS:
                //     // Could handle keys or just exit
                //     printf("Key pressed, exiting...\n");
                //     engine_close();
                //     free(event);
                //     goto end;
            }
            free(event);
        }

        engine_tick();
    }

end:
    engine_close();
    xcb_disconnect(connection);
}

void platform_resize_window(struct Aspect *windowSize) {
    if (!connection) return;

    xcb_configure_window(
        connection,
        window,
        XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
        (uint32_t[]){windowSize->width, windowSize->height}
    );
    xcb_flush(connection);
}

void platform_name_window(const char *name) {
    if (!connection) return;

    xcb_change_property(
        connection,
        XCB_PROP_MODE_REPLACE,
        window,
        XCB_ATOM_WM_NAME, XCB_ATOM_STRING,
        8, strlen(name), name);
    xcb_flush(connection);
}

#endif
