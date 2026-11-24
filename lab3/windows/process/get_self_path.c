#include "process.h"

bool process_get_self_path(char *buf, size_t size) {
    if (!buf || size < 2) {
        return false;
    }

    DWORD len = GetModuleFileNameA(NULL, buf, (DWORD)size);
    if (len == 0 || (size_t)len >= size) {
        return false;
    }

    return true;
}