#ifndef LOGGER_INTERNAL_H
#define LOGGER_INTERNAL_H

#include <stdbool.h>

extern const char *g_log_path;

bool logger_append(const char *path, const char *text);
bool logger_write(const char *fmt, ...);

#endif // LOGGER_INTERNAL_H