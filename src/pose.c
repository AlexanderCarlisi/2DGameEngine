#include "pose.h"
#include "world.h"

// TODO: World_config

void update_pose_meters(struct Pose* pose, float xMeters, float yMeters) {
    pose->xMeters = xMeters;
    pose->yMeters = yMeters;
    // pose->xPixels = xMeters * world->pixelsPerMeter;
    // pose->yPixels = yMeters * world->pixelsPerMeter;
}

void update_pose_pixels(struct Pose* pose, int xPixels, int yPixels) {
    pose->xPixels = xPixels;
    pose->yPixels = yPixels;
    // pose->xMeters = xPixels / world->pixelsPerMeter;
    // pose->yMeters = yPixels / world->pixelsPerMeter;
}

bool pose_equals(struct Pose* pose1, struct Pose* pose2) {
    return pose1->xMeters == pose2->xMeters && pose1->yMeters == pose2->yMeters;
}