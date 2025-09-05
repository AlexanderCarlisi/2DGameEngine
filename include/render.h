#ifndef RENDER_H
#define RENDER_H

#include "platform.h"

void (*init)(struct WindowConfig* window);
void (*clear)(struct WindowConfig* window, uint32_t color);
void (*draw_pixel)(struct WindowConfig* window, uint16_t x, uint16_t y, uint32_t color);
void (*interpolate_pixel)(struct WindowConfig* window, uint16_t x, uint16_t y, uint32_t color, float alpha);
void (*draw_shape)(struct WindowConfig* window, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color, int vertices);
void (*draw)(struct WindowConfig* window, float alpha);
void (*display)(struct WindowConfig* window);
void (*release_resources)(struct WindowConfig* window);
void (*set_aspects)(struct WindowConfig* window);

#endif
