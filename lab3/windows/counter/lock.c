#include "internal.h"

bool counter_lock(void) {
    if (!g_counter_mutex) {
        return false;
    }
    
    DWORD res = WaitForSingleObject(g_counter_mutex, INFINITE);
    return (res == WAIT_OBJECT_0 || res == WAIT_ABANDONED);
}