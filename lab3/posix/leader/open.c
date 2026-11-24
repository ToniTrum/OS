#include <fcntl.h>

#include "leader.h"
#include "internal.h"

#define LEADER_LOCK_PATH "/tmp/lab3_leader.lock"

int g_leader_fd = -1;
bool g_leader_owned = false;

bool leader_open(void) {
    if (g_leader_fd >= 0) {
        return true;
    }

    g_leader_fd = open(LEADER_LOCK_PATH, O_RDWR | O_CREAT | O_CLOEXEC, 0666);
    g_leader_owned = false;
    
    return g_leader_fd >= 0;
}