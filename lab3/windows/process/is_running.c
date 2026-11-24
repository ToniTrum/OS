#include "process.h"

bool process_is_running(process_handle_t *handle) {
    if (!handle || *handle == INVALID_PROC_HANDLE) {
        return false;
    }

    DWORD res = WaitForSingleObject(*handle, 0);
    if (res == WAIT_TIMEOUT) {
        return true;
    }

    CloseHandle(*handle);
    *handle = INVALID_PROC_HANDLE;
    
    return false;
}