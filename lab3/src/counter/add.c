#include "counter.h"
#include "counter/internal.h"

bool counter_add(int64_t delta) {
    if (!counter_lock()) {
        return false;
    }
    
    if (!g_counter_mem) {
        counter_unlock();
        return false;
    }

    g_counter_mem->value += delta;
    counter_unlock();
    
    return true;
}