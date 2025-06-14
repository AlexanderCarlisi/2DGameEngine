#ifndef APP_CONFIG_H
#define APP_CONFIG_H


// Structure representing a pixel by pixel size.
// Values in Pixels. {width, height}
typedef struct Aspect {
    int width;
    int height;
} Aspect;


// Application Configuration
// Information like the Window Name, Window size
// as well as Rendering information like the Aspect, Framerate.
typedef struct ApplicationConfig {
    char* window_name;
    struct Aspect window_aspect;
    struct Aspect render_aspect;
    int frames_per_second;
} ApplicationConfig;


struct ApplicationConfig* appconfig_get();
void appconfig_set(struct ApplicationConfig* config);

char* appconfig_get_name();
void appconfig_set_name(const char* name);

struct Aspect* appconfig_get_window_size();
void appconfig_set_window_size(struct Aspect aspect);
void appconfig_set_window_size_px(int pxWidth, int pxHeight);

struct Aspect* appconfig_get_resolution();
void appconfig_set_resolution(struct Aspect aspect);
void appconfig_set_resolution_px(int pxWidth, int pxHeight);

// If the Platform has updated the window size, then don't tell the platform that it did so.
void appconfig_platform_resized_window(struct Aspect aspect);

// If the Platform has updated the window size, then don't tell the platform that it did so.
void appconfig_platform_resized_window_px(int pxWidth, int pxHeight);

#endif // APP_CONFIG_H