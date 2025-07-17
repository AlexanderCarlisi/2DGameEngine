#include <stdint.h>
#include <stdbool.h>

#ifndef SHAPE_H
#define SHAPE_H

#include "pose.h"
#include "vector.h"

#ifndef SHAPE_PI
#define SHAPE_PI 3.14159265358979323846
#endif // SHAPE_PI

struct World; // WORLD_H


// A normalized magnitude, representing the Vertex of a Shape. 
// (x, y) : [0, 1]
// Bottom Left = (0, 0)
// Top Right = (1, 1)
// Layout: [int, int]
// Size: 8
typedef struct Vertex {
    int x;
    int y;
} Vertex;

DECLARE_VECTOR(VertexVector, vector_vertex, struct Vertex)
DECLARE_VECTOR(PoseVector, vector_pose, struct Pose)

// Shape object, responsible for generating and storing 2D Shapes.
// The data here is used for both Rendering and Physics.
// This Shape structure is made to be malliable, and allow for a lot of freedom.
// Do note that having a lot of verticies is performance intensive, and its not suggested to run isConvex too much
// if possible know if the shape is convex or not, or just simplify the collisions to always be or not be convex
// 
// A dynamic array of Verticies. Normalized between [0, 1], (0, 0) being bottom left.
// This way the size of your Object doesn't matter, and can be transposed to whatever Size freely.
// Each vertici needs to be processed anyways to place onto the screen, and for collision checks. So it really shouldn't add any overhead.
// ^ Requires one loop through the Array to be true, so gotta handle rendering and collisions in that one for loop.
// ^^ Simply find the proper pixel positions in Fixed Update, but only render them in the variable update.
// Layout: [Vector, Pose, uint32, bool]
// Size: 85(88), 53(56)
typedef struct Shape {
    struct VertexVector normalized_vertices;    // Dynamic Array of Normalized Verticies.
    struct PoseVector vertex_poses;             // Dynamic Array of Vertex Positions.
    struct Pose size;                           // Size of Shape, used to Transpose the Normalized Verticies.
    uint32_t color;                             // *Until Textures become a thing.
    bool convex;                                // Whether a Shape is Convex or Concave.
} Shape;


// Uses the Graham Scan algorithm to determine if the provided set of Vertices forms a convex shape.
// This engine allows users to have a lot of freedom with what
// shapes they want to use, but Convex Shapes vs. Concave Shapes have more 
// efficient algorithms, instead of running an algorithm to find if a shape
// is convex or concave, users will either need to run this to figure it out, or specify so when creating the shape.
// TODO: This.
bool shape_is_convex(struct VertexVector vertices);

/// @brief Initializes the provided Shape.
/// @param shape Ptr to Shape.
/// @param size Desired dimensions of Shape.
/// @param color To display the shape as in the Renderer.
/// @param convex Wether the shape is Convex or Concave.
/// @param vertices Dynamic Array of Normalized Vertices to define the outline of the Shape.
void shape_init(struct Shape* shape, struct Pose size, uint32_t color, bool convex, struct VertexVector vertices);

/// @brief Creates a Dynamic Array of Convex Vertices, for regular shape.
/// @param vertices 
VertexVector shape_create_vertices(int vertices);

/// @brief Initializes a new Shape, that's vertices are of a Square.
/// @param size To manipulate the width and height of the Box.
/// @param color To display the shape as in the Renderer.
struct Shape shape_create_box(struct Pose size, uint32_t color);


#endif // SHAPE_H