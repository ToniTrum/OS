#ifndef LEADER_H
#define LEADER_H

#include <stdbool.h>

bool leader_open(void);
bool leader_try_acquire(void);
void leader_release(void);
void leader_close(void);

#endif // LEADER_H