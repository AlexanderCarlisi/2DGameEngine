//
// GameObjects are the parts of the game.
// They have a Position, Size, Color, CollisionBox
// <p>
// I might want to seperate a Physical Position/Size and a Rendering Position/Size
// This would allow for Collisions that don't represent the look of an Object, it would be more versatile.
// <p>
// These Objects will also need some actual Physics: Acceleration, Velocity, Mass, Fiction(to calc coefficient)
//

//
// Two types of objects
// STATIC : Not affected by Physics, is still drawn every frame. Using functions to update Position will still work.
//  *** While static objects arent AFFECTED by physics, they will still affect other objects, unless stated otherwise.
// DYNAMIC : Affected by Physics, gravity and collisions. Ofcourse you can change these behaviors.
//

#include "world.h"
#include <stdint.h>

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


typedef enum ObjectType {
    STATIC,
    DYNAMIC
} ObjectType;

typedef struct GameObject {
    ObjectType objectType;
    Pose pose;
    Pose previousPose;
    float friction;
    uint32_t color;
    int shapeVerticies;

} GameObject;


//
// When updating a Pose structs values, it's recommended to use the provided functions, as it will update the other values. 
// (eg. if you update the Meters position using the function, it will update the Pixel positions using the proper conversion)
//
typedef struct Pose {
    int xMeters;
    int yMeters;
    int xPixels;
    int yPixels;
} Pose;

// Updates the provided Pose to the provided Meters, handles the conversion for Pixel values using the World settings.
void update_pose_meters(World* world, Pose* pose, int xMeters, int yMeters);

// Updates the provided Pose tot he provided Pixels, handles the conversion of Meter values using the World settings.
void update_pose_pixels(World* world, Pose* pose, int xPixels, int yPixels);

// Checks if two poses are equal in Meter Positions. Returns 1 if they are, 0 if they are not.
int pose_equals(Pose* pose1, Pose* pose2);


// Size is complicated because it relates to shapes, there will need to be some kind of Definition for Shapes,
// since it'll be easy to render them, but hard to calculate physics with them.
// I've decided that forcing all collision boxes to be rectangles would be too limiting to the users.
// //
// // When updating a Size structs values, it's recommended to use the provided functions, as it will update the other values.
// // (eg. if you update the meters size using the function, it will update the pixel sizes using the proper conversion)
// //
// // X and Y here mean how far they extend Horizontally and Vertically.
// //
// typedef struct Size {
//     int xMeters;
//     int yMeters;
//     int xPixels;
//     int yPixels;
// } Size;

// // Updates the provided Size to the provided Meters, handles the conversion for Pixel values using the World settings.
// void update_size_meters(World* world, Size* size, int xMeters, int yMeters);

// // Updates the provided Size tot he provided Pixels, handles the conversion of Meter values using the World settings.
// void update_size_pixels(World* world, Size* size, int xPixels, int yPixels);


#endif // GAME_OBJECT_H