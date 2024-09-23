#include "../include/Defines.h"
#include <stdio.h>

#ifdef _WIN32

void startTimer(Timer *timer) {
    QueryPerformanceFrequency(&timer->frequency);  // Obtenha a frequência do contador de alta resolução
    QueryPerformanceCounter(&timer->start_timepoint);  // Obtenha o tempo de início
}

void stopTimer(Timer *timer) {
    LARGE_INTEGER end_timepoint;
    QueryPerformanceCounter(&end_timepoint);  // Obtenha o tempo de término

    // Calcule a duração em segundos e depois converta para milissegundos
    double duration = (double)(end_timepoint.QuadPart - timer->start_timepoint.QuadPart) * 1000.0 / timer->frequency.QuadPart;

    printf("\n Tempo de execucao: %.3f ms\n", duration);
}

#else

void startTimer(Timer *timer) {
    clock_gettime(CLOCK_MONOTONIC, &timer->start_timepoint);  // Obtém o tempo de início
}

void stopTimer(Timer *timer) {
    struct timespec end_timepoint;
    clock_gettime(CLOCK_MONOTONIC, &end_timepoint);  // Obtém o tempo de término

    // Calcule a diferença de tempo
    long seconds = end_timepoint.tv_sec - timer->start_timepoint.tv_sec;
    long nanoseconds = end_timepoint.tv_nsec - timer->start_timepoint.tv_nsec;

    // Converta para milissegundos
    double duration = (seconds * 1000.0) + (nanoseconds / 1000000.0);

    printf("\n Tempo de execucao: %.3f ms\n", duration);
}

#endif