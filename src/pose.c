#include "pose.h"
#include "world_config.h"

void pose_update_meters(struct Pose* pose, float xMeters, float yMeters) {
	float ppm = worldconfig_get_ppm();
	pose->x_meters = xMeters;
	pose->y_meters = yMeters;
	pose->x_pixels = xMeters * ppm;
	pose->y_pixels = yMeters * ppm;
}

void pose_update_pixels(struct Pose* pose, float xPixels, float yPixels) {
	float ppm = worldconfig_get_ppm();
	pose->x_meters = xPixels / ppm;
	pose->y_meters = yPixels / ppm;
	pose->x_pixels = xPixels;
	pose->y_pixels = yPixels;
}

bool pose_equals(struct Pose* pose1, struct Pose* pose2) {
	return pose1->x_meters == pose2->x_meters && pose1->y_meters == pose2->y_meters;
}
