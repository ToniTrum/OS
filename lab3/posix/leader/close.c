#include <unistd.h>

#include "leader.h"
#include "internal.h"

void leader_close(void) {
    leader_release();

    if (g_leader_fd >= 0) {
        close(g_leader_fd);
        g_leader_fd = -1;
    }
}