// gcc src/*.c -Iinclude -o 2DGameEngine -lgdi32

// TODO: REFACTOR/ADDITION World Handler
// TODO: ADDITION: GameObject Shapes
// TODO: ADDITION: GameObject Textures
// TODO: ADDITION: World Physics, Collisions, CollisionBoxes

#include "platform.h"
#include "app_config.h"

int main() {
    ApplicationConfig appConfig = {
        .window_name = "MyGame",
        .frames_per_second = 60,
        .window_aspect = (Aspect) {.width=1280, .height=720},
        .render_aspect = (Aspect) {.width=1280, .height=720}
    };
    appconfig_init(&appConfig);
    platform_start();
    return 0;
}