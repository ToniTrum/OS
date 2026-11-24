#ifndef APP_INTERNAL_H
#define APP_INTERNAL_H

#include "process.h"

void app_spawn_copy(const char *self_path, const char *flag, const char *name, process_handle_t *handle);
void app_timer_worker(void *arg);
void app_cli_loop(void);

#endif // APP_INTERNAL_H