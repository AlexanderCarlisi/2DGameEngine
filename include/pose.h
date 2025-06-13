#ifndef POSE_H
#define POSE_H

#include "stdbool.h"

struct World; // WORLD_H


//
// When updating a Pose structs values, it's recommended to use the provided functions, as it will update the other values. 
// (eg. if you update the Meters position using the function, it will update the Pixel positions using the proper conversion)
//
typedef struct Pose {
    float xMeters;
    float yMeters;
    int xPixels;
    int yPixels;
} Pose;


// Updates the provided Pose to the provided Meters, handles the conversion for Pixel values using the World settings.
void update_pose_meters(struct Pose* pose, float xMeters, float yMeters);

// Updates the provided Pose tot he provided Pixels, handles the conversion of Meter values using the World settings.
void update_pose_pixels(struct Pose* pose, int xPixels, int yPixels);

// Checks if two poses are equal in Meter Positions. Returns 1 if they are, 0 if they are not.
bool pose_equals(struct Pose* pose1, struct Pose* pose2);

#endif // POSE_H