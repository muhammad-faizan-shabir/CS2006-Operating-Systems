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
# define maxThreads 20

void *worker(void* param)
{
    int x= *((int*)param);
    printf("Hello from thread %d - I was created in iteration %d\n",(int)pthread_self(),x);
    pthread_exit(NULL);
}

int main(int argc,char*argv[])
{
    if(argc!=2)
    {
        printf("Error! Exactly one argument <N> is needed\n");\
        return 0;
    }

    int N= atoi(argv[1]);
    if(N>maxThreads)
    {
        printf("Error! Max 20 threads allowed\n");
        return 0;
    }

    pthread_t threadsArr[maxThreads];
    int iteration[maxThreads];
    int counter=0;

    for(int i=0;i<N;i++)
    {
        iteration[i]=i;
        pthread_create(&threadsArr[i],NULL,worker,&iteration[i]);
        
        counter++;
        if(counter==4)
        {
            counter=0;
            sleep(1);
        }
        printf("I am thread %d. Created new thread (%d) in iteration %d...\n",(int)pthread_self(),(int)threadsArr[i],i);
    }

    for(int i=0;i<N;i++)
    {
        pthread_join(threadsArr[i],NULL);

    }
    return 0;
}