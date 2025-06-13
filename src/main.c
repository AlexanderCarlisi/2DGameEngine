// gcc src/*.c -Iinclude -o 2DGameEngine -lgdi32
// TODO: Rip out platform code, and place into own files.

// TODO: Fix Screen Size not being a Single instance

#include "engine.h"
#include "time.h"
#include <stdio.h>

#ifdef _WIN32

#include <windows.h>
#include "windows_renderer.h"


// Handles Windows Events
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            // Destroy the window and post a quit message
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            // Post a quit message to exit the message loop
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


// Main Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Create a Window Class
    const char CLASS_NAME[] = "Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc); // Registers the Window Class in the OS

    // Create the Window
    HWND hwnd = CreateWindowEx(
        0,                      // Optional Window Stypes
        CLASS_NAME,             // Window Class Name
        "Demo",        // Window Title
        WS_OVERLAPPEDWINDOW,    // Window Style

        // Position and size of Window
        // TODO: Variable screen sizes here
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,

        NULL,       // Parent Window
        NULL,       // Menu
        hInstance,  // Instance Handle
        NULL        // Additional App Data
    );

    if (hwnd == NULL) { // if the window handle doesn't exist, exit the program.
        printf("HWND is Null... exiting\n");
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    initialize_time_frequency(); // Initialize WinOS Timer Frequency
    engine_start(create_windows_renderer(&hwnd, 1280, 720));

    printf("Initialized Window\n");

    // Run the Message loop
    MSG msg = { };
    while (1) {
        // Check for messages and process them
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT || !engine_is_running()) {
                printf("...Closing Properly...\n");
                engine_close();
                return 0;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        engine_tick();

        // TODO: Work on this, for Framerates and what not
        Sleep(1); // ms
    }

    engine_close();
    return 0;
}


// TODO: All of linux, still not setup at all.
#else
// Unix main

#include <X11/Xlib.h>


#include <stdio.h>
#include <stdlib.h>

int main() {
    Display *display;
    Window window;
    XEvent event;
    int screen;
    
    // Open connection to the X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    
    screen = DefaultScreen(display);
    
    // Create a window
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 640, 480, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));
    
    // Select input events to be received by the window
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    
    // Display the window
    XMapWindow(display, window);
    
    // Event loop
    while (1) {
        XNextEvent(display, &event);
        
        // Handle the event
        if (event.type == Expose) {
            XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);
        }
        if (event.type == KeyPress)
            break;
    }
    
    // Close the display
    XCloseDisplay(display);
    return 0;
}

#endif