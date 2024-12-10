#include "world.h"
#include "game_object.h"


void world_init(struct World* self) {

}


void world_insert_object(struct World* self, struct GameObject* object) {

}


void world_update_physics(struct World* self) {
    
}

int world_create_object(struct GameObject* object) {
    object = (GameObject*) malloc(sizeof(GameObject))
    if (object == NULL) {
        printf(">>> GameObject Allocation Failure <<<");
        return 0;
    }
    return 1;
}

void world_destroy_object(struct GameObject* object) {

}