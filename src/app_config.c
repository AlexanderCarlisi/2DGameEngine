#include "app_config.h"
#include "stdint.h"
#include <stdlib.h>


static struct ApplicationConfig application_config = {
    .window_name = "Demo",
    .frames_per_second = 60,
    .window_aspect = (struct Aspect){.width=1280, .height=720},
    .render_aspect = (struct Aspect){.width=1280, .height=720}
};


char* appconfig_get_name() {
    return application_config.window_name;
}

void appconfig_set_name(const char* name) {
    // TODO: safety, buffers, and what not
}


struct Aspect* appconfig_get_window_size() {
    return &application_config.window_aspect;
}

void appconfig_set_window_size(struct Aspect aspect) {
    application_config.window_aspect = aspect;
    // Update platform
}

void appconfig_set_window_size_px(int pxWidth, int pxHeight) {
    appconfig_set_window_size((struct Aspect){.width=pxWidth, .height=pxHeight});
}


struct Aspect* appconfig_get_resolution() {
    return &application_config.render_aspect;
}

void appconfig_set_resolution(struct Aspect aspect) {
    application_config.render_aspect = aspect;
}

void appconfig_set_resolution_px(int pxWidth, int pxHeight) {
    appconfig_set_resolution((struct Aspect){.width=pxWidth, .height=pxHeight});
}


struct ApplicationConfig* appconfig_get() {
    return &application_config;
}

void appconfig_set(struct ApplicationConfig* config) {
    appconfig_set_name(config->window_name);
    appconfig_set_window_size(config->window_aspect);
    appconfig_set_resolution(config->render_aspect);
}