#ifndef COUNTER_INTERNAL_H
#define COUNTER_INTERNAL_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int64_t value;
} counter_mem_t;

extern counter_mem_t *g_counter_mem;

bool counter_lock(void);
void counter_unlock(void);

#endif // COUNTER_INTERNAL_H