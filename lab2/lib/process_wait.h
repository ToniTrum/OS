#ifndef PROCESS_WAIT_H
#define PROCESS_WAIT_H

#include <stdbool.h>
#include "process_run.h"

bool process_wait(process_handle_t handle, int *out_exit_code);

#endif // PROCESS_WAIT_H