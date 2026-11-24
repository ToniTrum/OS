#include <unistd.h>

#include "process.h"

bool process_get_self_path(char *buf, size_t size) {
    if (!buf || size < 2) {
        return false;
    }

    ssize_t len = readlink("/proc/self/exe", buf, size - 1);
    if (len <= 0 || (size_t)len >= size) {
        return false;
    }

    buf[len] = '\0';
    return true;
}