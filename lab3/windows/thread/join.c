#include <windows.h>

#include "thread.h"

bool thread_join(thread_t thread) {
    if (!thread) {
        return false;
    }

    HANDLE h = (HANDLE)thread;
    DWORD res = WaitForSingleObject(h, INFINITE);
    CloseHandle(h);
    
    return res == WAIT_OBJECT_0;
}