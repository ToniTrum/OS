#ifndef PROCESS_RUNNER_H
#define PROCESS_RUNNER_H

#include <stdbool.h>

#if defined(_WIN32)
    #include <windows.h>
    typedef HANDLE process_handle_t;
    #define INVALID_PROC_HANDLE NULL
#else
    #include <sys/types.h>
    typedef pid_t process_handle_t;
    #define INVALID_PROC_HANDLE ((pid_t)-1)
#endif

bool process_run(const char *path, char *const argv[], process_handle_t *out_handle);
bool process_wait(process_handle_t handle, int *out_exit_code);

#endif // PROCESS_RUNNER_H