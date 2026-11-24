#include "logger.h"
#include "logger/internal.h"

bool logger_write_busy(const char *name) {
    if (!name) {
        return false;
    }
    
    return logger_write("[BUSY] %s", name);
}