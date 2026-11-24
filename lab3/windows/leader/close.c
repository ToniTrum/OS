#include "leader.h"
#include "internal.h"

void leader_close(void) {
    leader_release();

    if (g_leader_mutex) {
        CloseHandle(g_leader_mutex);
        g_leader_mutex = NULL;
    }
}