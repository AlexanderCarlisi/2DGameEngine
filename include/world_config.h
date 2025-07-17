#ifndef WORLD_CONFIG_H
#define WORLD_CONFIG_H

/// Size of statically allocated Game Object Array.
#define WORLD_CONFIG_STATIC_ALLOC 100

typedef struct WorldConfig {
    float reallocation_ratio;   // ObjectsSize gets multiplied by this value when needed, or when reallocate is called.
    float pixels_per_meter;     // Used for Pose methods.
    float gravity_field;        // Gravity -> Newtons per Kg || Meters per Second/Second
} WorldConfig;

// Get a Pointer to the active World Config
struct WorldConfig* worldconfig_get();

// Get a Pointer to the Reallocation Ratio, Address persists throughout config changes.
float* worldconfig_get_realloc_ptr();

// Get a Pointer to Pixels per Meter value, Address persists throughout config changes.
float* worldconfig_get_ppm_ptr();

// Get a Pointer to the Gravity Field, Address persists throughout config changes.
float* worldconfig_get_gf_ptr();

// Update active config with new Reallocation Ratio. Memory address persists.
void worldconfig_set_realloc(float reallocRatio);

// Update active config with new Pixels per Meter proportion. Memory address persists.
void worldconfig_set_ppm(float pixelsPerMeter);

// Update active config with new Gravity Field. Memory address persists.
void worldconfig_set_gf(float gravityField);

// Updates active config with new values. Therefore, Memory addresses persist.
void worldconfig_set(struct WorldConfig* worldConfig);


#endif // WORLD_CONFIG_H