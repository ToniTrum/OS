#include "thread.h"

bool thread_join(thread_t thread) {
    return pthread_join(thread, NULL) == 0;
}