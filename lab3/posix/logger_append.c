#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "logger/internal.h"

bool logger_append(const char *path, const char *text) {
    if (!path || !text) {
        return false;
    }

    int fd = open(path, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0644);
    if (fd < 0) {
        return false;
    }

    struct flock lock = {0};
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    while (fcntl(fd, F_SETLKW, &lock) == -1) {
        if (errno != EINTR) {
            close(fd);
            return false;
        }
    }

    size_t len = strlen(text);
    size_t total_written = 0;
    bool ok = true;

    while (total_written < len) {
        ssize_t written = write(fd, text + total_written, len - total_written);
        if (written < 0) {
            if (errno == EINTR) {
                continue;
            }
            
            ok = false;
            break;
        }
        
        total_written += (size_t)written;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);
    
    return ok;
}