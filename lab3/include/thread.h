#ifndef THREAD_H
#define THREAD_H

#include <stdbool.h>

#if defined(_WIN32)
    typedef void *thread_t;
#else
    #include <pthread.h>
    typedef pthread_t thread_t;
#endif

typedef void (*thread_fn_t)(void *arg);

bool thread_create(thread_t *out_thread, thread_fn_t fn, void *arg);
bool thread_join(thread_t thread);
void thread_sleep_ms(unsigned int ms);

#endif // THREAD_H