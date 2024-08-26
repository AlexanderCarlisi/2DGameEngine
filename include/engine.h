#ifndef ENGINE_H
#define ENGINE_H

#define LOGIC_TIME_STEP 1.0f/60.0f

typedef enum {
    RUNNING,
    ENDED
} EngineState;

void engine_start();
void set_state(int newState);
// int get_state();

#endif