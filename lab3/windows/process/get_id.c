#include <windows.h>

#include "process.h"

int process_get_id(void) 
{
    return (int)GetCurrentProcessId();
}