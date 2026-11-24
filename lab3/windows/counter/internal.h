#ifndef COUNTER_WIN_INTERNAL_H
#define COUNTER_WIN_INTERNAL_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "counter/internal.h"

extern HANDLE g_counter_mutex;
extern HANDLE g_counter_map;

#endif // COUNTER_WIN_INTERNAL_H