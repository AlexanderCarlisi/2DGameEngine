#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "shape.h"
#include "stdint.h"
#include "stdbool.h"

struct GameObject; // GAME_OBJECT_H

// Layout: [Shape, funcptr, funcptr, uint32]
// Size: 124(128), 76
typedef struct CollisionBox {
    struct Shape shape;
    void (*on_collision_enter)(struct GameObject* self, struct GameObject* collidedObject);
    void (*on_collision_exit)(struct GameObject* self, struct GameObject* collidedObject);
    uint32_t debug_color;
    // bool collision_enabled;
} CollisionBox;

CollisionBox collision_box_create_debug(uint32_t debugColor, uint32_t shapeColor, struct Pose shapeSize);

#endif // COLLISION_BOX_H