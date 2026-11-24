#include <stddef.h>
#include <sys/mman.h>

#include "counter.h"
#include "internal.h"

void counter_close(void) {
    if (g_counter_mem) {
        munmap(g_counter_mem, sizeof(counter_mem_t));
        g_counter_mem = NULL;
    }

    if (g_counter_sem != SEM_FAILED) {
        sem_close(g_counter_sem);
        g_counter_sem = SEM_FAILED;
    }
}