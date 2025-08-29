#ifdef __linux__

#ifndef LINUXRENDERER_H
#define LINUXRENDERER_H

#include "render.h"
#include <xcb/xcb.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    Renderer base;            // Base Renderer struct
    xcb_connection_t* conn;   // Connection to X server
    xcb_screen_t* screen;     // Screen info
    xcb_window_t window;      // Window ID
    xcb_pixmap_t pixmap;      // Offscreen buffer
    uint32_t* framebuffer;    // Pixel buffer for software rendering
} LinuxRenderer;

// Initialization & cleanup
void linux_renderer_init(Renderer* self);
void linux_renderer_clear(Renderer* self, uint32_t color);
void linux_renderer_draw_pixel(Renderer* self, int x, int y, uint32_t color);
void linux_renderer_draw_shape(Renderer* self, int x, int y, uint32_t color, int vertices);
void linux_renderer_draw(Renderer* self, float alpha);
void linux_renderer_display(Renderer* self);
void linux_renderer_release_resources(Renderer* self);
Renderer* create_linux_renderer();

#endif // LINUXRENDERER_H
#endif // __linux__
