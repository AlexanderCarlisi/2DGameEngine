#ifdef _WIN32

#ifndef WINRENDERER_H
#define WINRENDERER_H

#include "render.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


typedef struct {
    Renderer base; // Renderer as first member so it's the start of the memory, meaning WindowsRenderer can be cast to a Renderer Struct
    HWND* hwnd; // Window Handle
    HDC hdc; // Device Connect Handle : Bridge between drawing functions and hardware
    HBITMAP bitmap; // Bitmap Handle : Pixel Data
    BITMAPINFO bitmapInfo; // Defines the Bitmaps properties
} WindowsRenderer;


void win_renderer_init(Renderer* self);
void win_renderer_clear(Renderer* self, uint32_t color);
void win_renderer_draw_pixel(Renderer* self, int x, int y, uint32_t color);
void win_renderer_draw_shape(Renderer* self, int x, int y, uint32_t color, int vertices);
void win_renderer_draw(struct Renderer* self, float alpha, struct GameObject*** objects);
void win_renderer_display(Renderer* self);
void win_renderer_release_resources(Renderer* self);
Renderer* create_windows_renderer(HWND* hwnd, int width, int height);


#endif // WINRENDERER_H
#endif // _WIN32