#include "leader.h"
#include "internal.h"

bool leader_try_acquire(void) {
    if (g_leader_owned) {
        return true;
    }
    
    if (!g_leader_mutex) {
        return false;
    }

    DWORD res = WaitForSingleObject(g_leader_mutex, 0);
    if (res == WAIT_OBJECT_0 || res == WAIT_ABANDONED) {
        g_leader_owned = true;
        return true;
    }

    return false;
}