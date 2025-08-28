#include "time.h"

#ifdef _WIN32

static LARGE_INTEGER frequency;
void initialize_time_frequency() {
    QueryPerformanceFrequency(&frequency);
}

float get_windows_time() {
    LARGE_INTEGER current;
    QueryPerformanceCounter(&current);
    return (float) current.QuadPart / (float) frequency.QuadPart;
}

float (*get_current_time) (void) = get_windows_time;


#else   // POSIX

// POSIX-specific time function
float get_psoix_time() {
    // struct timespec ts;
    // clock_gettime(CLOCK_MONOTONIC, &ts);
    // return (float) ts.tv_sec + (float) ts.tv_nsec / 1e9;
    return 0;
}

// Initialize the function pointer
float (*get_current_time) (void) = get_psoix_time;

#endif
