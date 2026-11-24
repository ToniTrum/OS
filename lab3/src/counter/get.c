#include "counter.h"
#include "counter/internal.h"

bool counter_get(int64_t *out_value) {
    if (!out_value || !counter_lock()) {
        return false;
    }
    
    if (!g_counter_mem) {
        counter_unlock();
        return false;
    }

    *out_value = g_counter_mem->value;
    counter_unlock();
    
    return true;
}