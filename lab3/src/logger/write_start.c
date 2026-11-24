#include "logger.h"
#include "logger/internal.h"

bool logger_write_start(const char *name) {
    if (!name) {
        return false;
    }
    
    return logger_write("[START] %s", name);
}