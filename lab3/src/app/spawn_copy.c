#include "app/internal.h"
#include "logger.h"
#include "process.h"

void app_spawn_copy(const char *self_path, const char *flag, const char *name, process_handle_t *handle) {
    if (process_is_running(handle)) {
        logger_write_busy(name);
        return;
    }

    char *argv[] = { (char *)self_path, (char *)flag, NULL };
    if (!process_spawn(self_path, argv, handle)) {
        logger_write_error(name, "failed to spawn");
    }
}