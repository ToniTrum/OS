#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "counter.h"
#include "internal.h"

#define SHM_NAME "/counter_shm"
#define SEM_NAME "/counter_sem"

counter_mem_t *g_counter_mem = NULL;
sem_t *g_counter_sem = SEM_FAILED;

bool counter_open(void) {
    g_counter_sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (g_counter_sem == SEM_FAILED) {
        return false;
    }

    if (!counter_lock()) {
        sem_close(g_counter_sem);
        g_counter_sem = SEM_FAILED;
        
        return false;
    }

    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        counter_unlock();
        sem_close(g_counter_sem);
        g_counter_sem = SEM_FAILED;
        
        return false;
    }

    struct stat st;
    if (fstat(fd, &st) == -1 || st.st_size < (off_t)sizeof(counter_mem_t)) {
        if (ftruncate(fd, (off_t)sizeof(counter_mem_t)) == -1) {
            close(fd);
            counter_unlock();
            sem_close(g_counter_sem);
            g_counter_sem = SEM_FAILED;
            
            return false;
        }
    }

    void *ptr = mmap(NULL, sizeof(counter_mem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    if (ptr == MAP_FAILED) {
        counter_unlock();
        sem_close(g_counter_sem);
        g_counter_sem = SEM_FAILED;
        
        return false;
    }

    g_counter_mem = (counter_mem_t *)ptr;
    counter_unlock();
    
    return true;
}