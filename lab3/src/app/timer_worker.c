#include <inttypes.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>

#include "app/internal.h"
#include "clock.h"
#include "counter.h"
#include "leader.h"
#include "logger.h"
#include "process.h"
#include "thread.h"

void app_timer_worker(void *arg) {
    atomic_bool *running = (atomic_bool *)arg;
    if (!running) {
        return;
    }

    char self_path[4096];
    bool has_self_path = process_get_self_path(self_path, sizeof(self_path));

    process_handle_t copy1 = INVALID_PROC_HANDLE;
    process_handle_t copy2 = INVALID_PROC_HANDLE;

    uint64_t now = clock_get_monotonic_ms();
    uint64_t next_inc_ms = now + 300ULL;
    uint64_t next_log_ms = now + 1000ULL;
    uint64_t next_spawn_ms = now + 3000ULL;
    bool was_leader = false;

    while (atomic_load(running)) {
        now = clock_get_monotonic_ms();

        (void)process_is_running(&copy1);
        (void)process_is_running(&copy2);

        while (now >= next_inc_ms) {
            counter_add(1);
            next_inc_ms += 300ULL;
        }

        if (leader_try_acquire()) {
            if (!was_leader) {
                next_log_ms = now + 1000ULL;
                next_spawn_ms = now + 3000ULL;
                was_leader = true;
            }

            if (now >= next_log_ms) {
                int64_t val = 0;
                if (counter_get(&val)) {
                    logger_write_counter(val);
                }
                next_log_ms += 1000ULL;
                if (next_log_ms <= now) {
                    next_log_ms = now + 1000ULL;
                }
            }

            if (now >= next_spawn_ms) {
                if (has_self_path) {
                    app_spawn_copy(self_path, "--copy1", "Copy 1", &copy1);
                    app_spawn_copy(self_path, "--copy2", "Copy 2", &copy2);
                } else {
                    logger_write_error("Timer", "failed to resolve executable path");
                }

                next_spawn_ms += 3000ULL;
                if (next_spawn_ms <= now) {
                    next_spawn_ms = now + 3000ULL;
                }
            }
        }

        thread_sleep_ms(20);
    }

    process_close(&copy1);
    process_close(&copy2);
    leader_release();
}