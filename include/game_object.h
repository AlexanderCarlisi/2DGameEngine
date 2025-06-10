//
// GameObjects are the parts of the game.
// They have a Position, Size, Color, CollisionBox
// <p>
// I might want to seperate a Physical Position/Size and a Rendering Position/Size
// This would allow for Collisions that don't represent the look of an Object, it would be more versatile.
// <p>
// These Objects will also need some actual Physics: Acceleration, Velocity, Mass, Fiction(to calc coefficient)
//

//
// Two types of objects
// STATIC : Not affected by Physics, is still drawn every frame. Using functions to update Position will still work.
//  *** While static objects arent AFFECTED by physics, they will still affect other objects, unless stated otherwise.
// DYNAMIC : Affected by Physics, gravity and collisions. Ofcourse you can change these behaviors.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// Includes
#include <stdint.h>
#include "pose.h"
#include "shape.h"

struct World; // WORLD_H


typedef enum ObjectType {
    STATIC,
    DYNAMIC
} ObjectType;


typedef struct GameObject {
    ObjectType objectType;
    Pose pose;
    Pose previousPose;
    float rotation;
    uint32_t color;
    Shape shape;
    int worldIndex;

} GameObject;


void initialize_gameobject(struct GameObject* obj, enum ObjectType objType, uint32_t color);


#endif // GAME_OBJECT_H