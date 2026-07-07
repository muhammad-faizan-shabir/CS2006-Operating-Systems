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

    // Open the same shared memory segment created by the first process
    shm_fd = shm_open(SHARED_MEM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory segment
    sem = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    close(shm_fd);

    // Use the semaphore
    printf("doosra\n");
    sem_post(sem);
   

    // Clean up
    munmap(sem, sizeof(sem_t));

    return 0;
}
