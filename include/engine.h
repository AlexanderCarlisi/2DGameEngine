//
// 2D Game Engine main class.
// Engine.tick() is the main loop of the program, it's encapsulated by OS code.
// When creating your own game using this Engine, you should be interfacing with this class to make changes.
//
#include "render.h"
#include "world.h"
#include "stdbool.h"

#ifndef ENGINE_H
#define ENGINE_H

// Initialize the engine
void engine_start(struct Renderer*);

// Update GameLogic, Physics, and Renderer
void engine_tick();

// Set the state of the engine | RUNNING or ENDED
void set_engine_state(bool isRunning);

// Closes the Engine, cleaning up resources | Call on Exit
void engine_close();

// Returns current state of the engine
bool engine_is_running();

// Returns a pointer to the world structure
struct World* engine_get_world_ptr();

// Returns a pointer to the Renderer
struct Renderer* engine_get_renderer_ptr();

#endif