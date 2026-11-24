#include <time.h>

#include "clock.h"

#define NS_PER_MS 1000000L

void clock_get_local(clock_time_t *out_time) {
    if (!out_time) {
        return;
    }

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    struct tm local_tm;
    localtime_r(&ts.tv_sec, &local_tm);

    out_time->year = local_tm.tm_year + 1900;
    out_time->month = local_tm.tm_mon + 1;
    out_time->day = local_tm.tm_mday;
    out_time->hour = local_tm.tm_hour;
    out_time->minute = local_tm.tm_min;
    out_time->second = local_tm.tm_sec;
    out_time->millisecond = (int)(ts.tv_nsec / NS_PER_MS);
}