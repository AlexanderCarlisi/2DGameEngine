#ifdef __linux__

#include "linux_renderer.h"
#include <xcb/xcb.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "app_config.h"
#include "world.h"

// TODO: maybe change the ints that are in the pixel functions
// Prolly make them Poses, or not ints, since int is kinda much yknow

void linux_renderer_clear(struct Renderer* self, uint32_t color) {
    struct Aspect* res = appconfig_get_resolution();
    size_t size = res->width * res->height;
    uint32_t* framebuffer = self->framebuffer;

    // Fill small buffer and memcpy across framebuffer
    uint32_t buffer[8];
    for (int i = 0; i < 8; i++) buffer[i] = color;
    for (size_t i = 0; i < size; i += 8) {
        memcpy(&framebuffer[i], buffer, sizeof(buffer));
    }
}

void linux_renderer_draw_pixel(struct Renderer* self, int x, int y, uint32_t color) {
    struct Aspect* res = appconfig_get_resolution();
    if (x < 0 || x >= res->width || y < 0 || y >= res->height) return;
    self->framebuffer[y * res->width + x] = color;
}

void linux_renderer_interpolate_pixel(struct Renderer* self, int x0, int y0, int x1, int y1, uint32_t color, float alpha) {
    int x = x0 + (int)((x1 - x0) * alpha);
    int y = y0 + (int)((y1 - y0) * alpha);
    linux_renderer_draw_pixel(self, x, y, color);
}

void linux_renderer_draw_shape(struct Renderer* self, int x, int y, uint32_t color, int vertices) {
    // TODO: implement shape drawing logic
}

void linux_renderer_draw(struct Renderer* self, float alpha) {
    struct Interval* interval_buffer = world_get_buffer_interval();
    struct Interval* interval_pool = world_get_pool_interval();

    for (size_t i = interval_buffer->start; i < interval_buffer->end; i++) {
        // Draw each active object on buffer
    }

    for (size_t i = interval_pool->start; i < interval_pool->end; i++) {
        // Draw each active object in pool
    }
}

void linux_renderer_display(struct Renderer* self) {
    LinuxRenderer* renderer = (LinuxRenderer*) self;

    // Push the framebuffer to the X server
    // TODO: Use xcb_put_image or xcb_copy_area with renderer->pixmap and renderer->window
    // Example:
    // xcb_put_image(renderer->conn, XCB_IMAGE_FORMAT_Z_PIXMAP, renderer->pixmap,
    //               renderer->gc, renderer->width, renderer->height, 0, 0, 0, 24,
    //               renderer->width * renderer->height * 4, (uint8_t*)renderer->framebuffer);
    // xcb_copy_area(renderer->conn, renderer->pixmap, renderer->window, renderer->gc, 0, 0, 0, 0,
    //               renderer->width, renderer->height);
    // xcb_flush(renderer->conn);
}

void linux_renderer_release_resources(struct Renderer* self) {
    LinuxRenderer* renderer = (LinuxRenderer*) self;
    if (renderer->framebuffer) free(renderer->framebuffer);
    // TODO: destroy pixmap, window, and disconnect from X server
    free(renderer);
}

void linux_renderer_set_aspects(struct Renderer* self) {
    LinuxRenderer* renderer = (LinuxRenderer*) self;
    struct Aspect* res = appconfig_get_resolution();

    if (renderer->framebuffer) {
        free(renderer->framebuffer);
        renderer->framebuffer = NULL;
    }
    
    renderer->framebuffer = (uint32_t*) calloc(res->width * res->height, sizeof(uint32_t));
    // TODO: create XCB pixmap and GC if needed
}

void linux_renderer_init(struct Renderer* self) {
    LinuxRenderer* renderer = (LinuxRenderer*) self;
    int screen_number;
    renderer->connection = xcb_connect(NULL, &screen_number);
    if (xcb_connection_has_error(r->connection)) {
        print("\n>>>Cannot connect to X Server<<<\n");
        free(renderer);
        return NULL;
    }

    // TODO: connect to X server
    // renderer->conn = xcb_connect(NULL, NULL);
    // renderer->screen = xcb_setup_roots_iterator(xcb_get_setup(renderer->conn)).data;
    // renderer->window = xcb_generate_id(renderer->conn);
    // create window and map it
    linux_renderer_set_aspects(self);
}

Renderer* create_linux_renderer(uint32_t width, uint32_t height) {
    LinuxRenderer* renderer = (LinuxRenderer*) malloc(sizeof(LinuxRenderer));
    memset(renderer, 0, sizeof(LinuxRenderer));
    
    
    struct Aspect* res = appconfig_get_resolution();
    struct Aspect* win = appconfig_get_window_size();
    renderer->base.framebuffer = (uint32_t*) calloc(res->width * res->height, sizeof(uint32_t));

    renderer->base.init = linux_renderer_init;
    renderer->base.clear = linux_renderer_clear;
    renderer->base.draw = linux_renderer_draw;
    renderer->base.draw_pixel = linux_renderer_draw_pixel;
    renderer->base.interpolate_pixel = linux_renderer_interpolate_pixel;
    renderer->base.draw_shape = linux_renderer_draw_shape;
    renderer->base.display = linux_renderer_display;
    renderer->base.release_resources = linux_renderer_release_resources;
    renderer->base.set_aspects = linux_renderer_set_aspects;

    return (Renderer*) renderer;
}

#endif // __linux__
