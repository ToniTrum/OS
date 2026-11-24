#include "counter.h"
#include "counter/internal.h"

bool counter_div(int64_t divisor) {
    if (divisor == 0 || !counter_lock()) {
        return false;
    }
    
    if (!g_counter_mem) {
        counter_unlock();
        return false;
    }

    g_counter_mem->value /= divisor;
    counter_unlock();
    return true;
}