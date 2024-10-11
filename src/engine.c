#include <stdio.h>
#include "engine.h"
#include "time.h"
#include "render.h"

static EngineState current_state = ENDED;
static const float FIXED_TIME_STEP = 1.0f / 60.0f;
static float accumulator = 0.0f;
static float lastTime = 0.0f;
static Renderer* renderer;

void engine_start(struct Renderer* render) {
    current_state = RUNNING;
    renderer = render;
}

void engine_tick() {
    float currentTime = get_current_time();
    float frameTime = currentTime - lastTime;
    lastTime = currentTime;
    accumulator += frameTime;

    // Fixed Update
    while (accumulator >= FIXED_TIME_STEP) {
        // Update Game Logic
        // Update Physics
        accumulator -= FIXED_TIME_STEP;
    }

    // Variable Update
    float alpha = accumulator / FIXED_TIME_STEP;
    // render->alpha
}

void set_engine_state(EngineState newState) {
    current_state = newState;
}

void engine_close() {
    // Clear Resources
    renderer->release_resources(renderer);
}

EngineState get_engine_state() {
    return current_state;
}