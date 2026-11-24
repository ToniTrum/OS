#include <windows.h>
#include <stdlib.h>

#include "thread.h"

typedef struct {
    thread_fn_t fn;
    void *arg;
} thread_trampoline_t;

static DWORD WINAPI thread_entry(LPVOID param) {
    thread_trampoline_t *t = (thread_trampoline_t *)param;
    thread_fn_t fn = t->fn;
    void *arg = t->arg;
    free(t);

    fn(arg);
    return 0;
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

    HANDLE h = CreateThread(NULL, 0, thread_entry, t, 0, NULL);
    if (!h) {
        free(t);
        return false;
    }

    *out_thread = (thread_t)h;
    return true;
}