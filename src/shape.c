#include "shape.h"
#include "pose.h"
#include <math.h>
#include "stdbool.h"
#include <stdlib.h>
#include "world.h"


// Function to calculate polar angle with respect to P0
// float calculatePolarAngle(Pose* p0, Pose* p1) {
//     return atan2(p1->yMeters - p0->yMeters, p1->xMeters - p0->xMeters);
// }



// [6, 5, 4, 3, 2, 1, 0]
// Divide the array until there is only 1 element
// [6], [5], [4], [3], [2], [1], [0]
// Merge and Sort into Pairs, and Single if odd
// [5, 6], [3, 4], [1, 2], [0]
// Merge and Sort into 4s, and Triple if odd
// [3, 4, 5, 6], [0, 1, 2]
// ^^ Repeat Pattern until Complete
// [0, 1, 2, 3, 4, 5, 6]

//
// Paramters: 
// the fucking array = Pose**
// the size of the fucking array = int
// 
// arrOfarrs = []
// for (int i = 0; i < thesizeofthefuckingarray; i++) {
//    
// }
//  
//
//
//
//









// // Merge Sort for sorting based on polar angle
// void mergeSort(Pose* vertices, int low, int high, Pose* p0) {
//     if (low < high) {
//         int mid = (low + high) / 2;
        
//         mergeSort(vertices, low, mid, p0);
//         mergeSort(vertices, mid + 1, high, p0);
        
//         merge(vertices, low, mid, high, p0);
//     }
// }

// // Merge function for Merge Sort
// void merge(Pose* vertices, int low, int mid, int high, Pose* p0) {
//     int n1 = mid - low + 1;
//     int n2 = high - mid;

//     Pose* left = (Pose*)malloc(n1 * sizeof(Pose));
//     Pose* right = (Pose*)malloc(n2 * sizeof(Pose));

//     for (int i = 0; i < n1; i++) {
//         left[i] = vertices[low + i];
//     }
//     for (int i = 0; i < n2; i++) {
//         right[i] = vertices[mid + 1 + i];
//     }

//     int i = 0, j = 0, k = low;

//     while (i < n1 && j < n2) {
//         float angleLeft = calculatePolarAngle(p0, &left[i]);
//         float angleRight = calculatePolarAngle(p0, &right[j]);

//         if (angleLeft < angleRight) {
//             vertices[k] = left[i];
//             i++;
//         } else if (angleLeft > angleRight) {
//             vertices[k] = right[j];
//             j++;
//         } else {  // If the angles are equal, keep the farthest one
//             float distLeft = left[i].xMeters * left[i].xMeters + left[i].yMeters * left[i].yMeters;
//             float distRight = right[j].xMeters * right[j].xMeters + right[j].yMeters * right[j].yMeters;

//             if (distLeft > distRight) {
//                 vertices[k] = left[i];
//                 i++;
//             } else {
//                 vertices[k] = right[j];
//                 j++;
//             }
//         }
//         k++;
//     }

//     while (i < n1) {
//         vertices[k] = left[i];
//         i++;
//         k++;
//     }

//     while (j < n2) {
//         vertices[k] = right[j];
//         j++;
//         k++;
//     }

//     free(left);
//     free(right);
// }

bool is_convex(Pose** verticesPtr, int length) {
    // Graham scan
    // Find the lowest x/y-cordinate point, searching for lowest y first.
    // Store this point P. This is an O(n) check

    // sort the vertices in increasing order of the angle they and point P make on the X-Axis.
    // pick the most optimal sorting algorithm for this. (needs research)
    // You do not need to compute the angle. Cosine can be computed using the Scalar Product.

    // What is Scalar Product?
    // Algebraically: 
    // sum of the products of corresponding entries in two sequences of numbers.
    // sumation( for i in array1/2.sharedLength: (array1[i] * array2[i]))
    // Geometrically:
    // The cosine of the angle between Two Vectors of length one is defined as their dot product.

    // Pose* vertices = *verticesPtr;
    // Pose* p0 = &vertices[0];
    // int p0Index = 0;
    // for (int i = 1; i < length; i++) {
    //     Pose* p1 = &vertices[i];
    //     if (p1->yMeters < p0->yMeters || (p1->yMeters == p0->yMeters && p1->xMeters < p0->xMeters)) {
    //         p0 = p1;
    //         p0Index = i;
    //     }
    // }

    // // Place p0 at first element
    // if (p0Index != 0) {
    //     Pose* temp = &vertices[0];
    //     vertices[0] = p0;
    //     vertices[p0Index] = temp;
    // }

    // // sort points by polar angle with P0, if several points have the same polar angle then only keep the farthest
    // // theta = arctan(y/x)
    // mergeSort(vertices, 1, length - 1, p0);

    // for (int i = 0; i < length; i++) {
    //     printf("Vertex %d: (%.2f, %.2f)\n", i, vertices[i].xMeters, vertices[i].yMeters);
    // }

    return false;
}


void create_shape_square(struct World* world, struct Shape* shape) {
    // TODO: Whatever this was supposed to be
    // shape->verticesCount = 4;
    // shape->vertices = calloc(shape->verticesCount, sizeof(Pose));
    // shape->convex = true;
    // update_pose_pixels(world, *shape->vertices[0], (float) world->screenWidthPx * 3/4.0f, (float) world->screenHeightPx * 3/4.0f);
    // update_pose_pixels(world, *shape->vertices[1], (float) world->screenWidthPx * 3/4.0f, (float) world->screenHeightPx * 1/4.0f);
    // update_pose_pixels(world, *shape->vertices[2], (float) world->screenWidthPx * 1/4.0f, (float) world->screenHeightPx * 3/4.0f);
    // update_pose_pixels(world, *shape->vertices[3], (float) world->screenWidthPx * 1/4.0f, (float) world->screenHeightPx * 1/4.0f);
}