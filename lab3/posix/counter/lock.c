#include <errno.h>
#include "internal.h"

bool counter_lock(void) {
    if (g_counter_sem == SEM_FAILED) {
        return false;
    }
    
    while (sem_wait(g_counter_sem) == -1) {
        if (errno != EINTR) {
            return false;
        }
    }
    
    return true;
}