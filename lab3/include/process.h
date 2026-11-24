#ifndef PROCESS_H
#define PROCESS_H

#include <stdbool.h>
#include <stddef.h>

#if defined(_WIN32)
    #include <windows.h>
    typedef HANDLE process_handle_t;
    #define INVALID_PROC_HANDLE NULL
#else
    #include <sys/types.h>
    typedef pid_t process_handle_t;
    #define INVALID_PROC_HANDLE ((pid_t)-1)
#endif

int process_get_id(void);
bool process_get_self_path(char *buf, size_t size);
bool process_spawn(const char *path, char *const argv[], process_handle_t *out_handle);
bool process_is_running(process_handle_t *handle);
void process_close(process_handle_t *handle);

#endif // PROCESS_H