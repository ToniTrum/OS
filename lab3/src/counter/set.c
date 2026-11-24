#include "counter.h"
#include "counter/internal.h"

bool counter_set(int64_t value) {
    if (!counter_lock()) {
        return false;
    }
    
    if (!g_counter_mem) {
        counter_unlock();
        return false;
    }

    g_counter_mem->value = value;
    counter_unlock();
    
    return true;
}