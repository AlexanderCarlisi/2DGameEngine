#include "engine.h"
#include <stdio.h>

static int current_state = STATE_ENDED;

void engine_start() {
    current_state = STATE_RUNNING;

    while (current_state == STATE_RUNNING) {
        printf("running");
    }
}

void set_state(int newState) {
    current_state = newState;
}