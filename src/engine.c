#include <stdio.h>
#include "engine.h"
#include "time.h"
#include "render.h"
#include "world.h"
#include "color.h"
#include "app_config.h"

static bool is_running = false;
static float accumulator = 0.0f;
static float last_time = 0.0f;
static Renderer* renderer;
static float* fixed_timestep;


void engine_start(struct Renderer* render) {
    fixed_timestep = appconfig_get_fps();
    is_running = true;
    renderer = render;
    renderer->init(renderer);
    printf("Engine Initialized\n");
}


void engine_tick() {
    // printf("Engine Tick\n");
    float currentTime = get_current_time();
    float frameTime = currentTime - last_time;
    last_time = currentTime;
    accumulator += frameTime;

    // Fixed Update
    while (accumulator >= *fixed_timestep) {
        // Update Game Logic
        // world_update_physics(&world);
        accumulator -= *fixed_timestep;
    }

    // Variable Update
    float alpha = accumulator / *fixed_timestep;
    renderer->clear(renderer, rgba(255, 255, 0, 255));
    renderer->draw(renderer, alpha);
    renderer->display(renderer);
    // printf("Engine Tick\n");
}


void engine_close() {
    // Clear Resources
	world_free();
    renderer->release_resources(renderer);
}


void set_engine_state(bool isRunning) {
    is_running = isRunning;
}


bool engine_is_running() {
    return is_running;
}

void engine_update_renderer_aspects() {
    renderer->set_aspects(renderer);
}

struct Renderer* engine_get_renderer_ptr() {
    return renderer;
}
