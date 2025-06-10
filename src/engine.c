#include <stdio.h>
#include "engine.h"
#include "time.h"
#include "render.h"
#include "world.h"
#include "color.h"
#include "stdbool.h"

static bool is_running = false;
static const float FIXED_TIME_STEP = 1.0f / 60.0f;
static float accumulator = 0.0f;
static float lastTime = 0.0f;
static Renderer* renderer;
static World world;

void engine_start(struct Renderer* render) {
    is_running = true;
    renderer = render;
    renderer->init(renderer);

    if (world_init(&world, &renderer->width, &renderer->height) == 0) {
        printf("\nengine_start(): World Init failure. \n");
        return;
    }

    printf("Engine Initialized\n");
}

void engine_tick() {
    // printf("Engine Tick\n");
    float currentTime = get_current_time();
    float frameTime = currentTime - lastTime;
    lastTime = currentTime;
    accumulator += frameTime;

    // Fixed Update
    while (accumulator >= FIXED_TIME_STEP) {
        // Update Game Logic
        world_update_physics(&world);
        accumulator -= FIXED_TIME_STEP;
    }

    // Variable Update
    float alpha = accumulator / FIXED_TIME_STEP;
    renderer->clear(renderer, rgba(255, 255, 0, 255));
    renderer->draw(renderer, alpha, &world.objects, world.objectsCount);
    renderer->display(renderer);
    // printf("Engine Tick\n");
}

void engine_close() {
    // Clear Resources
    world_deallocate(&world);
    renderer->release_resources(renderer);
}


void set_engine_state(bool isRunning) {
    is_running = isRunning;
}


bool engine_is_running() {
    return is_running;
}


struct World* get_world_ptr() {
    return &world;
}