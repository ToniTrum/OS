#include "internal.h"

void counter_unlock(void) {
    if (g_counter_sem != SEM_FAILED) {
        sem_post(g_counter_sem);
    }
}