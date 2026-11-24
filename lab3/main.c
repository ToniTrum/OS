#include "app.h"
#include "logger.h"

int main(int argc, char *argv[]) {
    logger_init("app.log");

    switch (app_parse_mode(argc, argv)) {
        case APP_MODE_COPY1: return app_run_copy1();
        case APP_MODE_COPY2: return app_run_copy2();
        case APP_MODE_MAIN:
        default: return app_run_main();
    }
}