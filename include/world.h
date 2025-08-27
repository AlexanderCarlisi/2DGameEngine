#ifndef WORLD_H
#define WORLD_H

#include "world_config.h"
#include "game_object.h"

DECLARE_VECTOR(GameObjectVector, vector_game_object, struct GameObject);

/**
 * @struct World
 * @brief Container for a 'World', holds functions and a WorldConfig used by
 * the world.
 *
 * @note For adding GameObjects to the Buffer and Pool @see world
 *
 * @var World::config
 * The WorldConfig used by the World. This will be set to the Active 
 * WorldConfig when this World is set as the Active World in world.
 * @see world_set_active
 *
 * @var World::init
 * Function Pointer to the World's initialization function. This function is
 * called the moment the World is loaded using @see world_load.
 * This should be used to place GameObjects on the Buffer and Pool, as the
 * space has been delegated for the World when this function is called.
 * @see worldconfig_get_buffer_interval
 * @see worldconfig_get_pool_interval
 *
 * @var World::start
 * Function Pointer to the World's start function. This function is called
 * when the World is set as the Active World in the world.
 * This should be used to set the Starting States of concurrent GameObjects
 * or finish up any buisness in init.
 * @see world_set_active
 *
 * @var World::loop
 * Function Pointer to the World's loop function. This function is called
 * every Fixed Update, when the World is set as the Active World in world.
 * @see world_set_active
 *
 * @var World::close
 * Function Pointer to the World's close function. This function is called
 * when this World was the active one, until the active world changed in
 * world.
 * @see world_set_active
 *
*/
typedef struct World {
	struct WorldConfig* config;
	void (*init)();
	void (*start)();
	void (*loop)();
	void (*close)();
} World;

/// @brief Reallocate the Object Pool.
/// @param newSize
/// @return Success of Reallocation.
/// @warning
bool world_realloc_pool(size_t newSize);

/// @brief Nullifies Objects within the Interval of the Object Buffer.
/// @param interval
/// @return Success of the operation.
bool world_remove_from_buffer(struct Interval* interval);

/// @brief Nullifies Objects within the Interval of the Object Pool.
/// @param interval
/// @return Success of the operation.
bool world_remove_from_pool(struct Interval* interval);

/// @brief Get the Interval of Active Game Objects on the Buffer.
struct Interval* world_get_buffer_interval();

/// @brief Get the Interval of Active Game Objects on the Pool.
struct Interval* world_get_pool_interval();

/// @brief Set the Interval of Active Game Objects on the Buffer.
/// @param interval
/// @return Validity of operation.
/// @warning Will not stop you from making NULL GameObjects active.
bool world_set_buffer_interval(struct Interval* interval);

/// @brief Set the Interval of Active Game Objects on the Pool.
/// @param interval
/// @return Validity of operation.
/// @warning Will not stop you from making NULL GameObjects active.
bool world_set_pool_interval(struct Interval* interval);

/// @brief Initialize the world with a new World.
/// @param world World to set as Active, loads the worldconfig, and setups necessary changes.
void world_load(struct World* world);

/// @brief Returns the Pointer to the GameObject on the Buffer at that Index.
/// @param index on buffer.
struct GameObject* world_buffer_get_object(size_t index);

/// @brief Returns the Pointer to the GameObject on the Pool at that Index.
/// @param index in pool.
struct GameObject* world_pool_get_object(size_t index);

/// @brief Set the Deallocation function for World Resources.
/// Users of the Engine should use this function to deallocate any memory
/// from their project. This function will be called by the Engine when the app
/// closes.
/// @param free_func Function Ptr.
void world_set_free_function(void (*free_func)());

/// @brief Using the Deallocation function provided, this will release the
/// resources of the worlds.
/// @see world_set_free_function
/// @note this Function will deallocate the Object Pool, all you need to
/// think about is deallocating your own code's resources.
void world_free();

#endif // WORLD_H
