#include <stdlib.h>
#include <string.h>

#include "../lib/process_run.h"

static char* format_command_line(char *const argv[]) {
    size_t length = 0;
    for (int i = 0; argv[i] != NULL; ++i) {
        length += strlen(argv[i]) + 3;
    }
    if (length == 0) return NULL;

    char *command_line = (char*)malloc(length + 1);
    if (!command_line) return NULL;
    
    command_line[0] = '\0';
    for (int i = 0; argv[i] != NULL; ++i) {
        strcat(command_line, "\"");
        strcat(command_line, argv[i]);
        strcat(command_line, "\" ");
    }
    
    return command_line;
}

bool process_run(const char *path, char *const argv[], process_handle_t *out_handle) {
    if (!path || !argv || !out_handle) {
        return false;
    }

    char *command_line = format_command_line(argv);
    if (!command_line) return false;

    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    BOOL ok = CreateProcessA(
        path,
        command_line,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );

    free(command_line);

    if (!ok) {
        *out_handle = INVALID_PROC_HANDLE;
        return false;
    }

    CloseHandle(pi.hThread);
    *out_handle = pi.hProcess;
    return true;
}