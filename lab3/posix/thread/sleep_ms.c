#include <errno.h>
#include <time.h>

#include "thread.h"

#define NS_PER_MS 1000000L

void thread_sleep_ms(unsigned int ms) {
    struct timespec req;
    req.tv_sec = (time_t)(ms / 1000);
    req.tv_nsec = (long)(ms % 1000) * NS_PER_MS;

    while (nanosleep(&req, &req) == -1 && errno == EINTR) {
    }
}