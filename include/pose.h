#ifndef POSE_H
#define POSE_H

#include "stdbool.h"

struct World; // WORLD_H

/// @struct Pose
/// @brief A position in the World.
///
/// @var Pose::x_meters
/// Horizontal Position, in meters.
///
/// @var Pose::y_meters
/// Verticle Position, in meters.
///
/// @var Pose::x_pixels
/// Horizontal Position, in pixels.
///
/// @var Pose::y_pixels
/// Verticle Position, in pixels.
/// 
/// @note Pose values should be updated using the related functions.
/// @see pose_update_meters
/// @see pose_update_pixels
///
/// @note Your game should be manipulating Meter values, updating Pixel values
/// will get messy, as the pixel values here are used directly by the Renderer.
///	
///	@note Meters and Pixel updates are proportional to each other based on the
///	WorldConfig. @file world_config.h
///	
/// @warning Updating one of these values on your own (outside the provided functions)
/// will cause problems if you aren't updating the Meters and Pixels values.
/// 
/// Layout: [float, float, int, int]
/// Size: 16 bytes
typedef struct Pose {
    float x_meters;
    float y_meters;
    int x_pixels;
    int y_pixels;
} Pose;


/// @brief Updates the Pose on new Meter coordinates.
/// @param pose Pose Pointer to update.
/// @param xMeters
/// @param yMeters
void pose_update_meters(struct Pose* pose, float xMeters, float yMeters);

/// @brief Updates the Pose on new Pixel coordinates.
/// @param pose Pose Pointer to update.
/// @param xPixels
/// @param yPixels
/// @warning It's suggested to stick with the Meters system, instead of manipulating
/// pixels directly.
void pose_update_pixels(struct Pose* pose, float xPixels, float yPixels);

/// @brief Checks if two poses are equal in Meter Positions.
/// @return True | False
bool pose_equals(struct Pose* pose1, struct Pose* pose2);

#endif // POSE_H
