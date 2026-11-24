#include <errno.h>
#include <sys/wait.h>

#include "process.h"

bool process_is_running(process_handle_t *handle) {
    if (!handle || *handle == INVALID_PROC_HANDLE) {
        return false;
    }

    int status = 0;
    pid_t res;
    do {
        res = waitpid(*handle, &status, WNOHANG);
    } while (res == -1 && errno == EINTR);

    if (res == 0) {
        return true;
    }

    *handle = INVALID_PROC_HANDLE;
    return false;
}