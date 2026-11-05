#include "../lib/process_wait.h"
#include <sys/wait.h>
#include <unistd.h>

bool process_wait(process_handle_t handle, int *out_exit_code) {
    if (handle == INVALID_PROC_HANDLE || !out_exit_code) {
        return false;
    }

    int status = 0;
    pid_t wait_pid = waitpid(handle, &status, 0);
    if (wait_pid == -1) {
        return false;
    }

    if (WIFEXITED(status)) {
        *out_exit_code = WEXITSTATUS(status);
        return true;
    } 
    else if (WIFSIGNALED(status)) {
        *out_exit_code = 128 + WTERMSIG(status);
        return true;
    }

    return false;
}