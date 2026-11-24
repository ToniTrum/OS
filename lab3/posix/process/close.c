#include <errno.h>
#include <sys/wait.h>

#include "process.h"

void process_close(process_handle_t *handle) {
    if (!handle || *handle == INVALID_PROC_HANDLE) {
        return;
    }

    int status = 0;
    pid_t res;
    do {
        res = waitpid(*handle, &status, WNOHANG);
    } while (res == -1 && errno == EINTR);

    *handle = INVALID_PROC_HANDLE;
}