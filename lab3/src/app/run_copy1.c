#include "app.h"
#include "counter.h"
#include "logger.h"

#define NAME "COPY_1"

int app_run_copy1(void) {
    logger_write_start(NAME);

    if (counter_open()) {
        counter_add(10);
        counter_close();
    } else {
        logger_write_error(NAME, "failed to open shared counter");
    }

    logger_write_exit(NAME);
    return 0;
}