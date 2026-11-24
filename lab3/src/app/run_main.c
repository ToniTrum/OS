#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>

#include "app.h"
#include "app/internal.h"
#include "counter.h"
#include "leader.h"
#include "logger.h"
#include "thread.h"

#define NAME "MAIN"

int app_run_main(void) {
    if (!counter_open()) {
        fprintf(stderr, "Failed to open shared counter\n");
        return 1;
    }

    if (!leader_open()) {
        fprintf(stderr, "Failed to open leader lock\n");
        counter_close();
        
        return 1;
    }

    if (!logger_write_start(NAME)) {
        fprintf(stderr, "Failed to write to log file\n");
        leader_close();
        counter_close();
        
        return 1;
    }

    atomic_bool running = true;
    thread_t timer_thread;
    if (!thread_create(&timer_thread, app_timer_worker, &running)) {
        fprintf(stderr, "Failed to start timer thread\n");
        leader_close();
        counter_close();
        
        return 1;
    }

    app_cli_loop();

    atomic_store(&running, false);
    thread_join(timer_thread);
    leader_close();
    counter_close();

    return 0;
}