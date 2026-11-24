#include <stdarg.h>
#include <stdio.h>

#include "clock.h"
#include "logger/internal.h"
#include "process.h"

bool logger_write(const char *fmt, ...) {
    clock_time_t ts;
    clock_get_local(&ts);

    int pid = process_get_id();

    char message[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);

    char line[640];
    snprintf(
        line,
        sizeof(line),
        "[%04d-%02d-%02d %02d:%02d:%02d.%03d] [PID %d] %s\n",
        ts.year, ts.month, ts.day,
        ts.hour, ts.minute, ts.second, ts.millisecond,
        pid,
        message
    );

    return logger_append(g_log_path, line);
}