#include <windows.h>
#include <string.h>

#include "logger/internal.h"

bool logger_append(const char *path, const char *text) {
    if (!path || !text) {
        return false;
    }

    HANDLE hFile = CreateFileA(
        path,
        FILE_APPEND_DATA,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD len = (DWORD)strlen(text);
    DWORD written = 0;
    BOOL ok = WriteFile(hFile, text, len, &written, NULL);

    CloseHandle(hFile);
    return ok && (written == len);
}