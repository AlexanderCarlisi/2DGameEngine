// TODO: LOWKEY REWRITE THIS WHOLE FUCKING THING OMG
// IT WOULD BE SICK ASF IF WINDOWS COULD HAVE THEIR OWN WORLD STRUCTS TPYE SHIT ONGOD

// gcc src/*.c -Iinclude -o 2DGameEngine -lgdi32

// TODO: REFACTOR/ADDITION World Handler
// TODO: ADDITION: GameObject Shapes
// TODO: ADDITION: GameObject Textures
// TODO: ADDITION: World Physics, Collisions, CollisionBoxes
// TODO: ADDITION/REFAC: Error Logging to File.

// TODO: Cleanup GameObject formatting
// TODO: Refactor World handling of GameObjects and Pool
// TODO: Refactor size variables with size_t
// TODO: UNIX impl
// TODO: CLEANUP, go through everything, lots of refactors, theres gonna be tons of uglyness
//
// TODO: Refactor Renderer to not be like a 'object' (maybe)
// TODO: This will probably never happen. but refactor the entire project to allow Multi-Windowness
//          Requires a rewrite of appconfig, the renderers, engine, and platform

// CURRENT:
//  = Collision Boxes
//  - Implement Rendering of Shapes / Collision Boxes
//      - Possibly start implementing the rotation on them.
//
//  - Before rending game objects, FIX how the World handles them.
//  - Game Objects were overhauled a bit
//      - World needs to handle them better, should be Creating objects in the World using a GOConfig.
//
//  - World's been overhauled, now its time to refactor the rest of the Code to work with it.
//
//  - Theres been some contemplation on storing pointers for frequently accessed values, and its a waste of memory
//  - Renderer is the main issue with this, but follow the errors ;)
//
//  =======
//  Implementing Unix support

#include "platform.h"
#include "app_config.h"

int main() {
    ApplicationConfig appConfig = {
        .window_name = "MyGame",
        .frames_per_second = 1/60.0,
        .window_aspect = (Aspect) {.width=1280, .height=720},
        .render_aspect = (Aspect) {.width=1280, .height=720}
    };
    appconfig_init(&appConfig);
    platform_start();
    return 0;
}
