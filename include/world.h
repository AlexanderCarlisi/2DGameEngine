#ifndef WORLD_H
#define WORLD_H

#include "game_object.h"

// World object, holds gameobjects, and whatever else I come up with
typedef struct World {
    GameObject** objects; // Dynamic Array of Pointers to GameObjects.
    int objectsCount; // Amount of Objects present in Objects Array.
    int objectsSize; // Current Size of Objects Array.
    float reallocationRatio; // ObjectsSize gets multiplied by this value when needed, or when reallocate is called.
    
    float pixelsPerMeter; // 10 px/m default. Used in pose conversion functions.
    float g; // g, gravity field. 9.8 N/Kg | m/s/s default.

    int* screenWidthPx;
    int* screenHeightPx;
} World;


// Initializes the World
int world_init(struct World* self, int* screenWidthPtr, int* screenHeightPtr);

// Add a GameObject to the world-> objects dynamic array, handles errors.
int world_insert_object(struct World* self, struct GameObject* objectptr);

// Update all GameObject Bodies, should be run every Tick at a fixed update rate.
void world_update_physics(struct World* self);

// Allocates a GameObject, calls world_insert_object automatically.
// Sets passed in Pointer value.
// Returns 0: Allocation Failure, 1: Allocation Successful
int world_create_object(struct World* self, struct GameObject** objectptr);

// Deallocates a GameObject, and removes it from the Dynamic Array.
// Doesn't automatically reallocate the Array, if you want to deallocate memory use @reallocate_objects function.
// param worldIndex should be provided from the GameObject you want to destroy.
// GameObjects store their index in the array so we can get efficient O(1) removals, with minimal memory overhead.
int world_destroy_object(struct World* self, int worldIndex);

// Reallocates Objects array, this allows for users of the Engine to optimize themselves selves without relying on automatic reallocations.
// It is recommended to do this whenever adding or removing inconsistant or large amounts of data at a time.
// You should change objectsSize and reallocationRatio based on your game's needs.
int world_reallocate_objects(struct World* self);

// Free all World resources.
void world_deallocate(struct World* self);

#endif // WORLD_H