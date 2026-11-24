#include "app.h"
#include "counter.h"
#include "logger.h"
#include "thread.h"

#define NAME "COPY_2"

int app_run_copy2(void) {
    logger_write_start(NAME);

    if (counter_open()) {
        counter_mul(2);
        thread_sleep_ms(2000);
        counter_div(2);
        counter_close();
    } else {
        logger_write_error(NAME, "failed to open shared counter");
    }

    logger_write_exit(NAME);
    return 0;
}