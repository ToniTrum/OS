#ifndef COUNTER_H
#define COUNTER_H

#include <stdbool.h>
#include <stdint.h>

bool counter_open(void);
void counter_close(void);

bool counter_get(int64_t *out_value);
bool counter_set(int64_t value);
bool counter_add(int64_t delta);
bool counter_mul(int64_t factor);
bool counter_div(int64_t divisor);

#endif // COUNTER_H