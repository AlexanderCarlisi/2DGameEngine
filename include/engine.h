#ifndef ENGINE_H
#define ENGINE_H

#define LOGIC_TIME_STEP 1.0f/60.0f

typedef enum {
    RUNNING,
    ENDED
} EngineState;

// Initialize the engine
void engine_start();

// Update GameLogic, Physics, and Renderer
void engine_tick();

// Set the state of the engine | RUNNING or ENDED
void set_engine_state(EngineState newState);

// Closes the Engine, cleaning up resources | Call on Exit
void engine_close();

// Returns current state of the engine
EngineState get_engine_state();

#endif