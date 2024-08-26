#include "engine.h"


#ifdef _WIN32
// Windows-specific main

#include <windows.h>


// Handles Windows Events
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


// Main Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    // Create a Window Class
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc); // Registers the Window Class in the OS

    // Create the Window
    HWND hwnd = CreateWindowEx(
        0,                      // Optional Window Stypes
        CLASS_NAME,             // Window Class Name
        "Sample Window",        // Window Title
        WS_OVERLAPPEDWINDOW,    // Window Style

        // Position and size of Window
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent Window
        NULL,       // Menu
        hInstance,  // Instance Handle
        NULL        // Additional App Data
    );

    if (hwnd == NULL) { // Why is this needed? seems redundent
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the Message loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        engine_start();
    }

    return 0;
}


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