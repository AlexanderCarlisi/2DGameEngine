/// TODO:
/// Higher level platform handler
/// Most users will go through this to
/// create new windows, and manage currently existing ones.
/// will be the new communication point for the platform renderers.
/// -
/// platform_initalize. This will create the first window of the game, and init the dyn array of windows.
/// platform_new_window, will append a new WindowInfo to the Dyn Arr, and Initialize it with provided args.
/// platform_set_window_name, size_t window index, const char* name
/// platform_set_window_size, size_t window index, struct Aspect* windowAspect
/// platform_set_window_resolution, size_t window index, struct Aspect* resolutionAspect
/// *Accessed by Engine
/// platform_iterate, iterates through the platforms User input system
/// platform_render, run the platform renderer

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include <stdbool.h>

#define PLATFORM_MAX_WINDOW_NAME 256    // Should be max Window Name length for Windows and Unix, needs to be tested.

/// @struct Aspect
/// A width and height representing pixels.
/// Layout [uint16, uint16]
/// Size 4(8), 4
typedef struct Aspect {
    uint16_t width;
    uint16_t height;
} Aspect;


/// @struct WindowConfig
/// Contains information consering that of a Window.
/// This information is used the same across platforms.
typedef struct WindowConfig {
    char window_name[PLATFORM_MAX_WINDOW_NAME];
    struct Aspect window_aspect;
    struct Aspect render_aspect;
    float frames_per_second;
} WindowConfig;


bool platform_initialize();

struct WindowConfig* platform_new_window(struct WindowConfig* windowConfig);

// After updating the config with your desired changes, call this to Refresh the renderer and whatnot
struct WindowConfig* platform_update_window(struct WindowConfig* config);

// Updates the Config, and updates platform side 'flush'
bool platform_set_window_name(struct WindowConfig* config, const char* name);
bool platform_set_window_size(struct WindowConfig* config, struct Aspect size);
bool platform_set_window_resolution(struct WindowConfig* config, struct Aspect res);

// bool for errors or somthin idk
bool platform_iterate();
bool platform_render();

// TODO: WINDOWS
#ifdef _WIN32
#endif

#ifdef __linux__
#include <xcb/xcb.h>

typedef struct X11Window {
    struct WindowConfig config;
    xcb_connection_t* connection;
    xcb_screen_t* screen;
    xcb_window_t window;
    xcb_pixmap_t pixmap;      // Offscreen buffer
    uint32_t* framebuffer;    // Pixel buffer for software rendering
} X11Window;

#endif // __linux__
#endif // PLATFORM_H
