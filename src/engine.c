#include <stdio.h>
#include "engine.h"
#include "time.h"

static EngineState current_state = EngineState.ENDED;
static const float FIXED_TIME_STEP = 1.0f / 60.0f;
static float accumulator = 0.0f;
static float lastTime = get_current_time();

void engine_start() {
    current_state = EngineState.RUNNING;

    #ifdef _WIN32 // Windows requires initialization of time frequency
    initialize_time_frequency();
    #endif
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