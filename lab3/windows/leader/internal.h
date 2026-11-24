#ifndef LEADER_WIN_INTERNAL_H
#define LEADER_WIN_INTERNAL_H

#include <windows.h>
#include <stdbool.h>

extern HANDLE g_leader_mutex;
extern bool g_leader_owned;

#endif // LEADER_WIN_INTERNAL_H