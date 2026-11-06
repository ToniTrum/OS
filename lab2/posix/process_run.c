#include <unistd.h>
#include <stdio.h>

#include "../lib/process_run.h"

bool process_run(const char *path, char *const argv[], process_handle_t *out_handle) {
    if (!path || !argv || !out_handle) {
        return false;
    }

    pid_t pid = fork();
    if (pid < 0) {
        *out_handle = INVALID_PROC_HANDLE;
        return false;
    }

    if (pid == 0) {
        execvp(path, argv);
        perror("execvp failed");
        _exit(127);
    }

    *out_handle = pid;
    return true;
}