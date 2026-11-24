#include <time.h>

#include "clock.h"

#define NS_PER_MS 1000000L

uint64_t clock_get_monotonic_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    
    return (uint64_t)ts.tv_sec * 1000ULL + (uint64_t)(ts.tv_nsec / NS_PER_MS);
}