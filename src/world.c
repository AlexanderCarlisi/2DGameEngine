#include "world.h"
#include "game_object.h"
#include "stdio.h"
#include "stdlib.h"
#include "color.h"
#include "pose.h"
#include "shape.h"
#include "app_config.h" 


int world_init(struct World* self) {
    struct Aspect* resolution = appconfig_get_resolution();

    // TODO: World Config
    self->pixelsPerMeter = 10;
    self->g = 9.8;

    // Initialize GameObject Dynamic Array
    self->reallocationRatio = 1.5;
    self->objectsCount = 1;
    self->objectsSize = 2;
    self->objects = (GameObject**) calloc(self->objectsSize, sizeof(GameObject*));
    if (self->objects == NULL) {
        printf(">>> world_init(): World->Objects Allocation Failure");
        return 0;
    }

    if (world_create_object(self, &self->objects[0]) == 0) {
        printf(">>> world_init(): GameObject Allocation Failure");
        return 0;
    }

    // Test Code
    GameObject* testObj = self->objects[0];
    testObj->color = rgba(0, 0, 255, 255);
    // create_shape_square(self, &testObj->shape);
    update_pose_pixels(&testObj->pose, resolution->width / 2, resolution->height / 2);
    update_pose_pixels(&testObj->previousPose, resolution->width / 2, resolution->height / 2);

    return 1;
}

int world_insert_object(struct World* self, struct GameObject* objectptr) {
    if (self->objects == NULL) return 0;
    self->objectsCount++;

    // Reallocate when needed
    if (self->objectsCount > self->objectsSize) {
        world_reallocate_objects(self);
    }

    objectptr->worldIndex = self->objectsCount - 1;
    self->objects[objectptr->worldIndex] = objectptr;
    return 1;
}

int world_create_object(struct World* self, struct GameObject** objectptr) {
    *objectptr = (GameObject*) malloc(sizeof(GameObject));
    if (*objectptr == NULL) {
        printf(">>> world_create_object(): GameObject Allocation Failure <<<");
        return 0;
    }
    if (world_insert_object(self, *objectptr) == 0) {
        printf(">>> world_create_object(): GameObject Insertion Failure <<<");
        return 0;
    }
    return 1;
}

int world_destroy_object(struct World* self, int worldIndex) {
    if (worldIndex < 0 || worldIndex >= self->objectsCount) {
        printf(">>> world_destroy_object(): Index out of Bounds <<<\n");
        return 0;
    }

    // Object to remove
    GameObject* target = self->objects[worldIndex];

    // Object at the end of the list
    int lastIndex = self->objectsCount - 1;
    GameObject* lastObject = self->objects[lastIndex];

    if (worldIndex != lastIndex) {
        // Move the last object to the deleted slot
        self->objects[worldIndex] = lastObject;
        lastObject->worldIndex = worldIndex;
    }

    // Null out and decrement
    self->objects[lastIndex] = NULL;
    self->objectsCount--;

    // Free the target object
    free(target);
    return 1;
}

int world_reallocate_objects(struct World* self) {    
    self->objectsSize *= self->reallocationRatio;
    GameObject** reallocated = (GameObject**) realloc(self->objects, self->objectsSize * sizeof(GameObject));
    if (reallocated == NULL) {
        printf("\n>>> world_insert_object(): Objects Reallocation Failure <<<\n");
        return 0;
    }
    self->objects = reallocated;
    return 1;
}

void world_deallocate(struct World* self) {
    for (int i = 0; i < self->objectsCount; i++) {
        free(self->objects[i]);
    }
    free(self->objects);
}

void world_update_physics(struct World* self) {
    // TODO: THIS
}