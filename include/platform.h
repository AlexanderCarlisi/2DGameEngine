#ifndef PLATFORM_H
#define PLATFORM_H

struct Aspect; // APP_CONFIG_H

void platform_start();
void platform_resize_window(struct Aspect* windowSize);
void platform_name_window(const char* name);

#ifdef __linux__
#include <xcb/xcb.h>

typedef struct X11Window {
  xcb_connection_t* connection;
  xcb_screen_t* screen;
  xcb_window_t window;
} X11Window;

struct X11Window* platform_get_x11_window();

#endif // __linux__

#endif // PLATFORM_H
