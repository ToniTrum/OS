#include <stdio.h>

#include "lib/process_run.h"
#include "lib/process_wait.h"

int main(void) {
    process_handle_t handle = INVALID_PROC_HANDLE;

#if defined(_WIN32)
    char *command = "C:\\Windows\\System32\\ping.exe";
    char *args[] = { "ping.exe", "127.0.0.1", "-n", "10", NULL };
#else
    char *command = "ping";
    char *args[] = { "ping", "127.0.0.1", "-c", "10", NULL };
#endif

    printf("[Parent] Starting child process in background...\n");
    if (!process_run(command, args, &handle)) {
        fprintf(stderr, "[ERROR] Failed to launch child process!\n");
        return 1;
    }

    int exit_code = -1;
    printf("[Parent] Waiting for child process...\n");
    if (!process_wait(handle, &exit_code)) {
        fprintf(stderr, "[ERROR] Error waiting for process!\n");
        return 1;
    }

    printf("[Parent] Child finished with exit code: %d\n", exit_code);
    return (exit_code == 0) ? 0 : 1;
}