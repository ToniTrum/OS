#include "counter.h"
#include "counter/internal.h"

bool counter_mul(int64_t factor) {
    if (!counter_lock()) {
        return false;
    }
    
    if (!g_counter_mem) {
        counter_unlock();
        return false;
    }

    g_counter_mem->value *= factor;
    counter_unlock();
    
    return true;
}