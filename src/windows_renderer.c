#ifdef _WIN32

#include "windows_renderer.h"
#include "game_object.h"
#include <windows.h>

void win_renderer_init(struct Renderer* self) {
    WindowsRenderer* renderer = (WindowsRenderer*) self;
    renderer->hdc = GetDC(*renderer->hwnd);

    // init bitmap info
    memset(&renderer->bitmapInfo, 0, sizeof(BITMAPINFO));
    renderer->bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    renderer->bitmapInfo.bmiHeader.biWidth = self->width;
    renderer->bitmapInfo.bmiHeader.biHeight = -self->height; // Top-down DIB
    renderer->bitmapInfo.bmiHeader.biPlanes = 1;
    renderer->bitmapInfo.bmiHeader.biBitCount = 32;
    renderer->bitmapInfo.bmiHeader.biCompression = BI_RGB;

    renderer->bitmap = CreateDIBSection(renderer->hdc, &renderer->bitmapInfo, DIB_RGB_COLORS, (void**) &self->framebuffer, NULL, 0);
    SelectObject(renderer->hdc, renderer->bitmap);
}

void win_renderer_clear(struct Renderer* self, uint32_t color) {
    size_t size = self->width * self->height;
    uint32_t* framebuffer = self->framebuffer;

    // Fill a small buffer with the color, then copy it across the framebuffer
    uint32_t buffer[8];
    for (int i = 0; i < 8; i++) {
        buffer[i] = color;
    }
    for (size_t i = 0; i < size; i += 8) {
        memcpy(&framebuffer[i], buffer, sizeof(buffer));
    }
}

void win_renderer_draw_pixel(struct Renderer* self, int x, int y, uint32_t color) {
    if (x < 0 || x >= self->width || y < 0 || y >= self->height) return;
    self->framebuffer[y * self->width + x] = color;
}

void win_renderer_interpolate_pixel(struct Renderer* self, int x0, int y0, int x1, int y1, uint32_t color, float alpha) {
    int x = (int) ((x1 - x0) * alpha);
    int y = (int) ((y1 - y0) * alpha);
    win_renderer_draw_pixel(self, x, y, color);
}

void win_renderer_draw_shape(struct Renderer* self, int x, int y, uint32_t color, int vertices) {
    // TODO
}

void win_renderer_draw(struct Renderer* self, float alpha, struct GameObject*** objects, int amountOfGameObjects) {
    // Drawing objects as singular pixels
    for (int i = 0; i < amountOfGameObjects; i++) {
        GameObject obj = *(*objects)[i]; // objects is a pointer to a Dynamic Array of GameObject Pointers | ;)
        if (!pose_equals(&obj.pose, &obj.previousPose)) {
            win_renderer_interpolate_pixel(self, obj.previousPose.xPixels, obj.previousPose.yPixels, obj.pose.xPixels, obj.pose.yPixels, obj.color, alpha);
        } else {
            win_renderer_draw_pixel(self, obj.pose.xPixels, obj.pose.yPixels, obj.color);
        }
    }

    // Drawing objects as Shapes
    // for (int i = 0; i < amountOfGameObjects; i++) {
        
    // }
}

void win_renderer_display(struct Renderer* self) {
    WindowsRenderer* renderer = (WindowsRenderer*) self;
    StretchDIBits(
        renderer->hdc,
        0, 0, self->width, self->height,
        0, 0, self->width, self->height,
        self->framebuffer,
        &renderer->bitmapInfo,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}

void win_renderer_release_resources(struct Renderer* self) {
    WindowsRenderer* renderer = (WindowsRenderer*)self;
    if (renderer->bitmap) {
        DeleteObject(renderer->bitmap);
    }
    if (renderer->hdc) {
        ReleaseDC(*renderer->hwnd, renderer->hdc);
    }
    if (renderer->hwnd) {
        DestroyWindow(*renderer->hwnd);
    }
    if (self->framebuffer) {
        free(self->framebuffer);
    }
    free(renderer);
}

Renderer* create_windows_renderer(HWND* hwnd, int width, int height) {
    WindowsRenderer* renderer = (WindowsRenderer*) malloc(sizeof(WindowsRenderer));
    memset(renderer, 0, sizeof(WindowsRenderer));
    renderer->base.width = width;
    renderer->base.height = height;
    renderer->base.framebuffer = (uint32_t*) calloc(width * height, sizeof(uint32_t));

    renderer->base.init = win_renderer_init;
    renderer->base.clear = win_renderer_clear;
    renderer->base.draw = win_renderer_draw;
    renderer->base.draw_pixel = win_renderer_draw_pixel;
    renderer->base.interpolate_pixel = win_renderer_interpolate_pixel;
    renderer->base.draw_shape = win_renderer_draw_shape;
    renderer->base.display = win_renderer_display;
    renderer->base.release_resources = win_renderer_release_resources;

    renderer->hwnd = hwnd;

    return (Renderer*) renderer;
}

#endif // _WIN32