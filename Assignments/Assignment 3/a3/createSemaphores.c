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

int main()
{
    sem_open(SEM1_NAME,  O_CREAT |O_RDWR, 0666, 1); // Initial value: 1 //O_CREAT |
    sem_open(SEM2_NAME,O_CREAT |O_RDWR, 0666, 0); // Initial value: 0
}