#include "world_config.h"

static struct WorldConfig world_config = {
	.buffer_interval = (struct Interval) {0, WORLD_CONFIG_OBJECT_BUFFER_SIZE - 1},
	.pool_interval = (struct Interval) {0, 199},
	.pool_size = 200,
    .reallocation_ratio = 1.5,
    .gravity_field = 9.8,
    .pixels_per_meter = 10
};

struct WorldConfig* worldconfig_get() {
    return &world_config;
}

struct Interval* worldconfig_get_buffer_interval() {
	return &world_config.buffer_interval;
}

struct Interval* worldconfig_get_pool_interval() {
	return &world_config.pool_interval;
}

size_t worldconfig_get_pool_size() {
	return world_config.pool_size;
}

float worldconfig_get_realloc() {
    return world_config.reallocation_ratio;
}

float worldconfig_get_ppm() {
    return world_config.pixels_per_meter;
}

float worldconfig_get_gf() {
    return world_config.gravity_field;
}


void worldconfig_set_pool_size(size_t poolSize) {
	world_config.pool_size = poolSize;
}

void worldconfig_set_realloc(float reallocRatio) {
    world_config.reallocation_ratio = reallocRatio;
}

void worldconfig_set_ppm(float pixels_per_meter) {
    world_config.pixels_per_meter = pixels_per_meter;
}

void worldconfig_set_gf(float gravityField) {
    world_config.gravity_field = gravityField;
}

void worldconfig_set(struct WorldConfig* worldConfig) {
	world_config.buffer_interval = worldConfig->buffer_interval;
	world_config.pool_interval = worldConfig->pool_interval;
	world_config.pool_size = worldConfig->pool_size;
    world_config.reallocation_ratio = worldConfig->reallocation_ratio;
    world_config.gravity_field = worldConfig->gravity_field;
    world_config.pixels_per_meter = worldConfig->pixels_per_meter;
}
