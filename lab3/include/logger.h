#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>
#include <stdint.h>

void logger_init(const char *log_path);

bool logger_write_start(const char *name);
bool logger_write_counter(int64_t value);
bool logger_write_exit(const char *name);
bool logger_write_busy(const char *name);
bool logger_write_error(const char *source, const char *message);

#endif // LOGGER_H