#ifndef TIMER_H
#define TIMER_H

#include "Defines.h"
#ifdef _WIN32
#include <windows.h>
#else
#endif

typedef struct Timer {
#ifdef _WIN32
    LARGE_INTEGER start_timepoint;
    LARGE_INTEGER frequency;
#else
    struct timespec start_timepoint;
#endif
} Timer;

void startTimer(Timer *timer);
void stopTimer(Timer *timer);

#endif