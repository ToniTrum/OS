#include "../lib/process_wait.h"

bool process_wait(process_handle_t handle, int *out_exit_code) {
    if (handle == INVALID_PROC_HANDLE || !out_exit_code) {
        return false;
    }

    DWORD wait_result = WaitForSingleObject(handle, INFINITE);
    if (wait_result != WAIT_OBJECT_0) {
        CloseHandle(handle);
        return false;
    }

    DWORD code = 0;
    if (!GetExitCodeProcess(handle, &code)) {
        CloseHandle(handle);
        return false;
    }

    *out_exit_code = (int)code;
    CloseHandle(handle);
    return true;
}