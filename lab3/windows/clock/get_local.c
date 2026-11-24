#include <windows.h>

#include "clock.h"

void clock_get_local(clock_time_t *out_time) {
    if (!out_time) {
        return;
    }

    SYSTEMTIME st;
    GetLocalTime(&st);

    out_time->year = (int)st.wYear;
    out_time->month = (int)st.wMonth;
    out_time->day = (int)st.wDay;
    out_time->hour = (int)st.wHour;
    out_time->minute = (int)st.wMinute;
    out_time->second = (int)st.wSecond;
    out_time->millisecond = (int)st.wMilliseconds;
}