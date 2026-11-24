#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "thread.h"

void thread_sleep_ms(unsigned int ms) {
    Sleep((DWORD)ms);
}