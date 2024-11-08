//
// GameObjects are the parts of the game.
// They have a Position, Size, Color, CollisionBox
// <p>
// I might want to seperate a Physical Position/Size and a Rendering Position/Size
// This would allow for Collisions that don't represent the look of an Object, it would be more versatile.
// <p>
// These Objects will also need some actual Physics: Acceleration, Velocity, Mass, Fiction(to calc coefficient)
// 

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

typedef struct GameObject {

    int poseX;
    int poseY;


} GameObject;


#endif // GAME_OBJECT_H