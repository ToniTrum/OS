#include "logger.h"
#include "logger/internal.h"

bool logger_write_error(const char *source, const char *message) {
    if (!source || !message) {
        return false;
    }
    
    return logger_write("[ERROR] %s: %s", source, message);
}