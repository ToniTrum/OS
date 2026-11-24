#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app/internal.h"
#include "counter.h"
#include "process.h"

void app_cli_loop(void) {
    printf("PID %d started.\n", process_get_id());
    printf("Commands: <number> to set counter | 'g' to get counter | 'q' to quit\n");

    char buf[128];
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        buf[strcspn(buf, "\r\n")] = '\0';
        if (buf[0] == '\0') {
            continue;
        }

        if (strcmp(buf, "q") == 0 || strcmp(buf, "quit") == 0) {
            break;
        }

        if (strcmp(buf, "g") == 0 || strcmp(buf, "get") == 0) {
            int64_t val = 0;
            if (counter_get(&val)) {
                printf("Current counter: %" PRId64 "\n", val);
            }
            continue;
        }

        char *end = NULL;
        errno = 0;
        long long parsed = strtoll(buf, &end, 10);
        if (errno == 0 && end != buf && *end == '\0') {
            if (counter_set((int64_t)parsed)) {
                printf("Counter set to %" PRId64 "\n", (int64_t)parsed);
            }
        } else {
            printf("Unknown command. Enter an <number>, 'g', or 'q'.\n");
        }
    }
}