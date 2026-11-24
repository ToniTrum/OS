#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
} clock_time_t;

void clock_get_local(clock_time_t *out_time);
uint64_t clock_get_monotonic_ms(void);

#endif // CLOCK_H