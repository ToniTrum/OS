#include "leader.h"
#include "internal.h"

#define LEADER_MUTEX_NAME "Local\\leader_mutex"

HANDLE g_leader_mutex = NULL;
bool g_leader_owned = false;

bool leader_open(void) {
    if (g_leader_mutex) {
        return true;
    }

    g_leader_mutex = CreateMutexA(NULL, FALSE, LEADER_MUTEX_NAME);
    g_leader_owned = false;
    
    return g_leader_mutex != NULL;
}