#include "world.h"
#include <string.h>

DEFINE_VECTOR(GameObjectVector, vector_game_object, struct GameObject);

static struct GameObject object_buffer[WORLD_CONFIG_OBJECT_BUFFER_SIZE];
static struct GameObjectVector object_pool;
static struct Interval interval_buffer;
static struct Interval interval_pool;
static void (*free_function)();

bool world_realloc_pool(size_t newSize) {
	if (object_pool.data == NULL) {
		return vector_game_object_init(&object_pool, newSize);

	} else if (object_pool.size == newSize) {
		return vector_game_object_realloc(&object_pool);

	} else {
		return vector_game_object_realloc_set(&object_pool, newSize);
	}
}

bool interval_bounds_check(struct Interval* interval, size_t realEnd) {
	return interval->start >= 0 && interval->start <= interval->end && interval->end <= realEnd;
}

bool world_remove_from_buffer(struct Interval* interval) {
	if (!interval_bounds_check(interval, WORLD_CONFIG_OBJECT_BUFFER_SIZE)) {
		return false;
	}
	for (size_t i = interval->start; i < interval->end; i++) {
	  	struct GameObject* go = &object_buffer[i];
	  	vector_collision_box_free(&go->collider_vector);
		memset(go, 0, sizeof(struct GameObject));
	}
	return true;
}

bool world_remove_from_pool(struct Interval* interval) {
	if (!interval_bounds_check(interval, object_pool.size)) {
		return false;
	}
	for (size_t i = interval->start; i < interval->end; i++) {
	  	struct GameObject* go = &object_pool.data[i];
	  	vector_collision_box_free(&go->collider_vector);
		memset(go, 0, sizeof(struct GameObject));
	}
	return true;
}

struct Interval* world_get_buffer_interval() {
	return &interval_buffer;
}

struct Interval* world_get_pool_interval() {
	return &interval_pool;
}

bool world_set_buffer_interval(struct Interval* interval) {
	if (interval_bounds_check(interval, WORLD_CONFIG_OBJECT_BUFFER_SIZE)) {
		interval_buffer.start = interval->start;
		interval_pool.end = interval->end;
		return true;
	}
	return false;
}

bool world_set_pool_interval(struct Interval* interval) {
	if (interval_bounds_check(interval, object_pool.size)) {
		interval_pool.start = interval->start;
		interval_pool.end = interval->end;
		return true;
	}
	return false;
}

struct GameObject* world_buffer_get_object(size_t index) {
	return &object_buffer[index];
}

struct GameObject* world_pool_get_object(size_t index) {
	return &object_pool.data[index];
}

void world_load(struct World* world) {
	// TODO: setup proper error handling
	worldconfig_set(world->config);
	world_realloc_pool(worldconfig_get_pool_size());
	world_set_buffer_interval(worldconfig_get_buffer_interval());
	world_set_pool_interval(worldconfig_get_pool_interval());
}

void world_set_free_function(void (*free_func)()) {
	free_function = free_func;
}

void world_free() {
	vector_game_object_free(&object_pool);
	free_function();
}
