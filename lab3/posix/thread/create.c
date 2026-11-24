#include <stdlib.h>

#include "thread.h"

typedef struct {
    thread_fn_t fn;
    void *arg;
} thread_trampoline_t;

static void *thread_entry(void *param) {
    thread_trampoline_t *t = (thread_trampoline_t *)param;
    thread_fn_t fn = t->fn;
    void *arg = t->arg;
    free(t);

    fn(arg);
    return NULL;
}

bool thread_create(thread_t *out_thread, thread_fn_t fn, void *arg) {
    if (!out_thread || !fn) {
        return false;
    }

    thread_trampoline_t *t = (thread_trampoline_t *)malloc(sizeof(*t));
    if (!t) {
        return false;
    }

    t->fn = fn;
    t->arg = arg;

    if (pthread_create(out_thread, NULL, thread_entry, t) != 0) {
        free(t);
        return false;
    }

    return true;
}