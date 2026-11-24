#include "logger.h"
#include "logger/internal.h"

const char *g_log_path = "app.log";

void logger_init(const char *log_path) {
    if (log_path && log_path[0] != '\0') {
        g_log_path = log_path;
    }
}