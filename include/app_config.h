#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#define MAX_WINDOW_NAME_LENGTH 256    // Should be max Window Name length for Windows and Unix, needs to be tested.


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
    char window_name[MAX_WINDOW_NAME_LENGTH];
    struct Aspect window_aspect;
    struct Aspect render_aspect;
    int frames_per_second;
} ApplicationConfig;


///
/// Get functions return Pointers to memory addresses that don't change!
///

struct ApplicationConfig* appconfig_get();
char* appconfig_get_name();
struct Aspect* appconfig_get_window_size();
struct Aspect* appconfig_get_resolution();


///
/// These functions are called by OS'.
/// Do not call them yourself, unless you know what you're doing.
///

void appconfig_platform_resized_window(struct Aspect aspect);
void appconfig_platform_resized_window_px(int pxWidth, int pxHeight);


///
/// These functions are for you to set the Application Config's data.
/// They will update on the platform side.
///

void appconfig_set(struct ApplicationConfig* config);
void appconfig_set_name(const char* name);
void appconfig_set_window_size(struct Aspect aspect);
void appconfig_set_window_size_px(int pxWidth, int pxHeight);
void appconfig_set_resolution(struct Aspect aspect);
void appconfig_set_resolution_px(int pxWidth, int pxHeight);

/// @brief Call this in Main. Overwrites the default Configuration.
/// @param config 
void appconfig_init(struct ApplicationConfig* config);

#endif // APP_CONFIG_H