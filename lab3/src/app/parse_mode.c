#include <string.h>

#include "app.h"

app_mode_t app_parse_mode(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--copy1") == 0) {
            return APP_MODE_COPY1;
        }
        
        if (strcmp(argv[i], "--copy2") == 0) {
            return APP_MODE_COPY2;
        }
    }
    
    return APP_MODE_MAIN;
}