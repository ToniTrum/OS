#include <windows.h>

#include "clock.h"

uint64_t clock_get_monotonic_ms(void) {
    return (uint64_t)GetTickCount64();
}