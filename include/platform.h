#ifndef PLATFORM_H
#define PLATFORM_H

struct Aspect; // APP_CONFIG_H

void platform_start();
void platform_resize_window(struct Aspect* windowSize);
void platform_name_window(const char* name);

#endif // PLATFORM_H