#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/mman.h>
#include <semaphore.h>

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#define SEM1_NAME "semaphore1"
#define SEM2_NAME "semaphore2"

int main(int argc,char*argv[])
{
    sem_t *sem1, *sem2;

    // Open semaphores
    sem1 = sem_open(SEM1_NAME, O_RDWR);
    sem2 = sem_open(SEM2_NAME, O_RDWR);


    char *shared_memory;
    
    int shmid;
    shmid=shmget((key_t)2345, 1024, 0666);
    shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment


    while(1)
    {
        sem_wait(sem2);
        printf("You wrote : %s\n",(char*)shared_memory);
        sem_post(sem1);

    }

    // Clean up
    sem_close(sem1);
    sem_close(sem2);

    return 0;

    

}