#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#define SHARED_MEM_NAME "/my_shared_memory"
#define SEMAPHORE_NAME "/my_semaphore"

int main() {
    int shm_fd;
    sem_t *sem;

    // Create/open shared memory segment
    shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(sem_t));

    // Map the shared memory segment
    sem = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    close(shm_fd);

    // Initialize semaphore
    sem_init(sem, 1, 0);  // Initial value: 1

    // Use the semaphore
    printf("Process 1: Waiting for semaphore...\n");
    sem_wait(sem);
    printf("Process 1: Semaphore acquired.\n");
    

    // Clean up
    sem_destroy(sem);
    munmap(sem, sizeof(sem_t));
    shm_unlink(SHARED_MEM_NAME);

    return 0;
}
