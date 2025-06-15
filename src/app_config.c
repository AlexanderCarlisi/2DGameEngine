#include "app_config.h"
#include "stdint.h"
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "render.h"
#include "engine.h"


static struct ApplicationConfig application_config = {
    .window_name = "Unconfigured App Config!",
    .frames_per_second = 1/24.0,
    .window_aspect = (struct Aspect){.width=480, .height=480},
    .render_aspect = (struct Aspect){.width=480, .height=480}
};

void appconfig_init(struct ApplicationConfig* config) {
    application_config = *config;
}

char* appconfig_get_name() {
    return application_config.window_name;
}

void appconfig_set_name(const char* name) {
    if (name) {
        strncpy(application_config.window_name, name, MAX_WINDOW_NAME_LENGTH - 1);
        application_config.window_name[MAX_WINDOW_NAME_LENGTH - 1] = '\0'; // Force termination char
        platform_name_window(application_config.window_name);
    }
}

struct Aspect* appconfig_get_window_size() {
    return &application_config.window_aspect;
}

void appconfig_set_window_size(struct Aspect aspect) {
    application_config.window_aspect = aspect;
    platform_resize_window(&application_config.window_aspect);
    engine_update_renderer_aspects();
}

void appconfig_set_window_size_px(int pxWidth, int pxHeight) {
    appconfig_set_window_size((struct Aspect){.width=pxWidth, .height=pxHeight});
}

void appconfig_platform_resized_window(struct Aspect aspect) {
    application_config.window_aspect = aspect;
    engine_update_renderer_aspects();
}

void appconfig_platform_resized_window_px(int pxWidth, int pxHeight) {
    appconfig_platform_resized_window((struct Aspect){.width=pxWidth, .height=pxHeight});
}

struct Aspect* appconfig_get_resolution() {
    return &application_config.render_aspect;
}

void appconfig_set_resolution(struct Aspect aspect) {
    application_config.render_aspect = aspect;
    engine_update_renderer_aspects();
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

float* appconfig_get_fps() {
    return &application_config.frames_per_second;
}