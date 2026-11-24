#include "logger.h"
#include "logger/internal.h"

bool logger_write_exit(const char *name) {
    if (!name) {
        return false;
    }
    
    return logger_write("[EXIT] %s", name);
}