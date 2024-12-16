#include "world.h"
#include "game_object.h"
#include "stdio.h"
#include "stdlib.h"


int world_init(struct World* self, int* screenWidthPtr, int* screenHeightPtr) {
    self->pixelsPerMeter = 10;
    self->g = 9.8;
    self->screenWidthPx = screenWidthPtr;
    self->screenHeightPx = screenHeightPtr;

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

void world_update_physics(struct World* self) {
    
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
    if (worldIndex > self->objectsSize - 1 || worldIndex < 0) {
        printf(">>> world_destory_object(): Index out of Bounds, you should be passing GameObject.worldIndex <<<");
        return 0;
    }

    self->objectsCount--;
    GameObject* toSwap = self->objects[self->objectsCount];
    self->objects[toSwap->worldIndex] = NULL;
    self->objects[worldIndex] = toSwap;
    toSwap->worldIndex = worldIndex;
    free(self->objects[worldIndex]);
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