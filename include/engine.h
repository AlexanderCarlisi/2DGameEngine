//
// 2D Game Engine main class.
// Engine.tick() is the main loop of the program, it's encapsulated by OS code.
// When creating your own game using this Engine, you should be interfacing with this class to make changes.
//
#include "render.h"
#include "world.h"

#ifndef ENGINE_H
#define ENGINE_H

typedef enum {
    RUNNING,
    ENDED
} EngineState;

// Initialize the engine
void engine_start(struct Renderer*);

// Update GameLogic, Physics, and Renderer
void engine_tick();

// Set the state of the engine | RUNNING or ENDED
void set_engine_state(EngineState newState);

// Closes the Engine, cleaning up resources | Call on Exit
void engine_close();

// Returns current state of the engine
EngineState get_engine_state();

// Returns a pointer to the world structure
struct World* get_world_ptr();


#endif