//
// World houses all the GameObjects, and handles Physics updates
// <p>
// Unit standards will need to exist for Physics to happen.
// Distance: Meters
// Mass: Kilograms
// Default Gravity Field: 9.8 N/kg

#include "game_object.h"

#ifndef WORLD_H
#define WORLD_H


// World object, holds gameobjects, and whatever else I come up with
typedef struct World {
    GameObject* objects; // Dynamic Array of GameObjects
    int objectCount = 1;
    float pixelsPerMeter = 3; // 3 Pixles = 1 Meter, this is the default setting, and can be changed.

} World;


// Initializes the World
void world_init(struct World* self);

// Add a GameObject to the world-> objects dynamic array, handles errors.
void world_insert_object(struct World* self, struct GameObject* object);

// Update all GameObject Bodies, should be run every Tick at a fixed update rate.
void world_update_physics(struct World* self);

// Allocates a GameObject, calls world_insert_object automatically.
// Sets passed in Pointer value.
// Returns 0: Allocation Failure, 1: Allocation Successful
int world_create_object(struct GameObject* object);

// Deallocates a GameObject, and removes it from the Dynamic Array.
void world_destroy_object(struct GameObject* object);


#endif // WORLD_H