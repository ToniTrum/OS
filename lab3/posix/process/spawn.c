#include <unistd.h>

#include "process.h"

bool process_spawn(const char *path, char *const argv[], process_handle_t *out_handle) {
    if (!path || !argv || !out_handle) {
        return false;
    }

    pid_t pid = fork();
    if (pid < 0) {
        *out_handle = INVALID_PROC_HANDLE;
        return false;
    }

    if (pid == 0) {
        execv(path, argv);
        _exit(127);
    }

    *out_handle = pid;
    return true;
}