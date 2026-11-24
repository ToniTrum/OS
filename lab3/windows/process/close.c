#include "process.h"

void process_close(process_handle_t *handle) {
    if (!handle || *handle == INVALID_PROC_HANDLE) {
        return;
    }

    CloseHandle(*handle);
    *handle = INVALID_PROC_HANDLE;
}