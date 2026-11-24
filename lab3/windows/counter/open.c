#include "counter.h"
#include "internal.h"

#define SHM_NAME   "Local\\counter_shm"
#define MUTEX_NAME "Local\\counter_mutex"

counter_mem_t *g_counter_mem = NULL;
HANDLE g_counter_mutex = NULL;
HANDLE g_counter_map = NULL;

bool counter_open(void) {
    g_counter_mutex = CreateMutexA(NULL, FALSE, MUTEX_NAME);
    if (!g_counter_mutex) {
        return false;
    }

    if (!counter_lock()) {
        CloseHandle(g_counter_mutex);
        g_counter_mutex = NULL;
        
        return false;
    }

    g_counter_map = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        (DWORD)sizeof(counter_mem_t),
        SHM_NAME
    );
    if (!g_counter_map) {
        counter_unlock();
        CloseHandle(g_counter_mutex);
        g_counter_mutex = NULL;
        
        return false;
    }

    g_counter_mem = (counter_mem_t *)MapViewOfFile(
        g_counter_map,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        sizeof(counter_mem_t)
    );
    if (!g_counter_mem) {
        CloseHandle(g_counter_map);
        g_counter_map = NULL;
        counter_unlock();
        CloseHandle(g_counter_mutex);
        g_counter_mutex = NULL;
        
        return false;
    }

    counter_unlock();
    return true;
}