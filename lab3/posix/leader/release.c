#include <fcntl.h>

#include "leader.h"
#include "internal.h"

void leader_release(void) {
    if (g_leader_fd < 0 || !g_leader_owned) {
        return;
    }

    struct flock lock = {0};
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    fcntl(g_leader_fd, F_SETLK, &lock);
    g_leader_owned = false;
}