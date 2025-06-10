// uint32_t represents Color: 4 Bytes (alpha, red, green, blue)

#include <stdint.h>
#include "game_object.h"

#ifndef RENDER_H
#define RENDER_H

typedef struct Renderer {
    void (*init)(struct Renderer* self);
    void (*clear)(struct Renderer* self, uint32_t color);
    void (*draw_pixel)(struct Renderer* self, int x, int y, uint32_t color);
    void (*interpolate_pixel)(struct Renderer* self, int x0, int y0, int x1, int y1, uint32_t color, float alpha);
    void (*draw_shape)(struct Renderer* self, int x, int y, uint32_t color, int vertices);
    void (*draw)(struct Renderer* self, float alpha, struct GameObject*** objects, int amountOfGameObjects);
    void (*display)(struct Renderer* self);
    void (*release_resources)(struct Renderer* self);

    uint32_t* framebuffer;
    int width, height;
} Renderer;



#endif