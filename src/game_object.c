#include "game_object.h"
#include "world.h"

void update_pose_meters(struct World* world, struct Pose* pose, int xMeters, int yMeters) {
    pose->xMeters = xMeters;
    pose->yMeters = yMeters;
    pose->xPixels = xMeters * world->pixelsPerMeter;
    pose->yPixels = yMeters * world->pixelsPerMeter;
}

void update_pose_pixels(struct World* world, struct Pose* pose, int xPixels, int yPixels) {
    pose->xPixels = xPixels;
    pose->yPixels = yPixels;
    pose->xMeters = xPixels / world->pixelsPerMeter;
    pose->yMeters = yPixels / world->pixelsPerMeter;
}

int pose_equals(struct Pose* pose1, struct Pose* pose2) {
    return pose1->xMeters == pose2->xMeters && pose1->yMeters == pose2->yMeters;
}