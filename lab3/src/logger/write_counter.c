#include <inttypes.h>

#include "logger.h"
#include "logger/internal.h"

bool logger_write_counter(int64_t value) {
    return logger_write("[COUNTER] %" PRId64, value);
}