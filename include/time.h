#ifndef TIME_H
#define TIME_H


#ifdef _WIN32   // WINDOWS
#include <windows.h>

void initialize_time_frequency();
float get_windows_time();

#else   // PSOIX
#include <time.h>

float get_psoix_time();

#endif  // _WIN32


float (*get_current_time) (void);

#endif // TIME_H