//
// World houses all the GameObjects, and handles Physics updates
// <p>
// Unit standards will need to exist for Physics to happen.
// Distance: Meters
// Mass: Kilograms
// Default Gravity Field: 9.8 N/kg
#ifndef WORLD_H
#define WORLD_H


// World object, holds gameobjects, and whatever else I come up with
typedef struct World {




} World;


void world_update_physics(struct World* self);


#endif // WORLD_H