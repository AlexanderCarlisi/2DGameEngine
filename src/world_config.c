#include "world_config.h"

static struct WorldConfig world_config = {
    .reallocation_ratio = 1.5,
    .gravity_field = 9.8,
    .pixels_per_meter = 10
};

struct WorldConfig* worldconfig_get() {
    return &world_config;
}

float* worldconfig_get_realloc_ptr() {
    return &world_config.reallocation_ratio;
}

float* worldconfig_get_ppm_ptr() {
    return &world_config.pixels_per_meter;
}

float* worldconfig_get_gf_ptr() {
    return &world_config.gravity_field;
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
    world_config.reallocation_ratio = worldConfig->reallocation_ratio;
    world_config.gravity_field = worldConfig->gravity_field;
    world_config.pixels_per_meter = worldConfig->pixels_per_meter;
}