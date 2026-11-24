#ifndef COUNTER_POSIX_INTERNAL_H
#define COUNTER_POSIX_INTERNAL_H

#include <semaphore.h>
#include "counter/internal.h"

extern sem_t *g_counter_sem;

#endif // COUNTER_POSIX_INTERNAL_H