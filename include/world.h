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
    float pixelsPerMeter = 3; // 3 Pixles = 1 Meter, this is the default setting, and can be changed.


} World;


void world_update_physics(struct World* self);


#endif // WORLD_H