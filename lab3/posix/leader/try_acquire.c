#include <fcntl.h>

#include "leader.h"
#include "internal.h"

bool leader_try_acquire(void) {
    if (g_leader_owned) {
        return true;
    }
    
    if (g_leader_fd < 0) {
        return false;
    }

    struct flock lock = {0};
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(g_leader_fd, F_SETLK, &lock) == 0) {
        g_leader_owned = true;
        return true;
    }

    return false;
}