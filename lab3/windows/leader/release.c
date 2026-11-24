#include "leader.h"
#include "internal.h"

void leader_release(void) {
    if (g_leader_mutex && g_leader_owned) {
        ReleaseMutex(g_leader_mutex);
        g_leader_owned = false;
    }
}