#include <stdint.h>
#include <stdbool.h>

#ifndef SHAPE_H
#define SHAPE_H

#include "pose.h"
struct World; // WORLD_H


// Shape object, responsible for generating and storing 2D Shapes.
// The data here is used for both Rendering and Physics.
// This Shape structure is made to be malliable, and allow for a lot of freedom.
// Do note that having a lot of verticies is performance intensive, and its not suggested to run isConvex too much
// if possible know if the shape is convex or not, or just simplify the collisions to always be or not be convex
typedef struct Shape {
    // Verticies are relative and offset to the GameObjects current pose. (0, 0) being center of GameObject.
    struct Pose* vertices; // dynamic array of Poses that represent Vertices.
    int verticesCount; // Not suggested to set this yourself, use the functions supplied for you.
    uint32_t color;
    bool convex; // store the isConvex function return here to prevent unnessessary calls, instead of running the algorithm you can also explictly set its state here.
} Shape;


// Uses the Graham Scan algorithm to determine if the provided set of Vertices forms a convex shape.
// This engine allows users to have a lot of freedom with what
// shapes they want to use, but Convex Shapes vs. Concave Shapes have more 
// efficient algorithms, instead of running an algorithm to find if a shape
// is convex or concave, users will either need to run this to figure it out, or specify so when creating the shape.
bool is_convex(struct Pose** verticesPtr, int length);


// helper function to initialize a Shape.
void create_shape_square(struct World* world, struct Shape* shape);



#endif // SHAPE_H