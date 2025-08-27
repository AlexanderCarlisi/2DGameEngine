#ifndef WORLD_CONFIG_H
#define WORLD_CONFIG_H

#include <stddef.h>

/// Size of statically allocated Game Object Array.
#define WORLD_CONFIG_OBJECT_BUFFER_SIZE 100


/**
 * @struct Interval
 * @brief An inclusive interval, generally used for Buffers and Pools.
 * Layout: [size_t, size_t]
 * Size: 16, 8
*/
typedef struct Interval {
	size_t start;
	size_t end;
} Interval;


/**
 * @struct WorldConfig
 * @brief Settings and Information on a World and it's data.
 * 
 * @var WorldConfig::buffer_interval
 * Interval of Active Game Objects on the Buffer. Objects outside of this Interval are not considered for Physics Updates, or Rendering.
 * 
 * @var WorldConfig::pool_interval
 * Interval of Active Game Objects on the Pool. Objects outside of this Interval are not considered for Physics Updates, or Rendering.
 *
 * @var WorldConfig::pool_size
 * Starting size of the WorldHandler's Pool when this Config is Loaded. Will not realloc unless necessary.
 * @note this value does not update to changes in the WorldHandler. @see world_handler_get_pool_size
 *
 * @var WorldConfig::reallocation_ratio
 * Ratio to use when automatically reallocating the Object Pool. This is only used when attempting to overflow the Pool.
 *
 * @var WorldConfig::pixels_per_meter
 * Pixels / Meter conversion, this is used in Pose math. @see struct Pose
 * TODO: Contemplate this some more, this being a float doesn't really make sense 10.5 / 1 is a weird fraction, and there is no half pixel.
 *
 * @var WorldConfig::gravity_field
 * The applied Gravity on Dynamic GameObjects. In units of Newtons/Kg || Meters per Second/Second
*/
typedef struct WorldConfig {
	struct Interval buffer_interval;
	struct Interval pool_interval;
	size_t pool_size;
    float reallocation_ratio;
	float pixels_per_meter;
    float gravity_field;
} WorldConfig;


/// @brief Get a Pointer to the active World Config
struct WorldConfig* worldconfig_get();

/// @brief Get the active World Config's buffer interval.
struct Interval* worldconfig_get_buffer_interval();

/// @brief Get the active World Config's pool interval.
struct Interval* worldconfig_get_pool_interval();

/// @brief Get a Pointer to the Pool Size of the active World Config, Address Persists throughout config changes.
/// @note This pointer is not the same as the actual Pool Size, just how it was configured when the World Config was first loaded.
size_t worldconfig_get_pool_size();

/// @brief Get a Pointer to the Reallocation Ratio, Address persists throughout config changes.
float worldconfig_get_realloc();

/// @brief Get a Pointer to Pixels per Meter value, Address persists throughout config changes.
float worldconfig_get_ppm();

/// @brief Get a Pointer to the Gravity Field, Address persists throughout config changes.
float worldconfig_get_gf();

/// @brief Update active config with a new Pool Size. Memory address persists.
/// @note Doesn't automatically reallocate the Object Pool.
void worldconfig_set_pool_size(size_t poolSize);

/// @brief Update active config with new Reallocation Ratio. Memory address persists.
void worldconfig_set_realloc(float reallocRatio);

/// @brief Update active config with new Pixels per Meter proportion. Memory address persists.
void worldconfig_set_ppm(float pixelsPerMeter);

/// @brief Update active config with new Gravity Field. Memory address persists.
void worldconfig_set_gf(float gravityField);

/// @brief Updates active config with new values. Therefore, Memory addresses persist.
void worldconfig_set(struct WorldConfig* worldConfig);


#endif // WORLD_CONFIG_H
