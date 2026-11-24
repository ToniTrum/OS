#ifndef APP_H
#define APP_H

typedef enum {
    APP_MODE_MAIN = 0,
    APP_MODE_COPY1,
    APP_MODE_COPY2
} app_mode_t;

app_mode_t app_parse_mode(int argc, char *argv[]);
int app_run_main(void);
int app_run_copy1(void);
int app_run_copy2(void);

#endif // APP_H