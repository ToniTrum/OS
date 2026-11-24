#include "internal.h"

void counter_unlock(void) {
    if (g_counter_mutex) {
        ReleaseMutex(g_counter_mutex);
    }
}