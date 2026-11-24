#include "counter.h"
#include "internal.h"

void counter_close(void) {
    if (g_counter_mem) {
        UnmapViewOfFile(g_counter_mem);
        g_counter_mem = NULL;
    }
    
    if (g_counter_map) {
        CloseHandle(g_counter_map);
        g_counter_map = NULL;
    }
    
    if (g_counter_mutex) {
        CloseHandle(g_counter_mutex);
        g_counter_mutex = NULL;
    }
}