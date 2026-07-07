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
#define max_threads 10

char buffer[max_threads][1000];

typedef struct
{
    int threadNum;
} threadArg;

void *worker(void*param)
{
    char fileName[100];
    threadArg * obj=(threadArg*)param;
    int threadNum=obj->threadNum;
    int i;
    for(i=0;buffer[threadNum][i]!='\0';i++)
    {
        fileName[i]=buffer[threadNum][i];
    }
    fileName[i]='\0';

    printf("Thread number %d with ID %ld started to work\n",threadNum+1,pthread_self());

    int file=open(fileName,O_RDONLY);

    if(file==-1)
    {
        printf("Error opening file  in thread number: %d\n",threadNum+1);
        pthread_exit(NULL);
    }

    int ch;
    i=0;
    while(read(file,&ch,1)>0)
    {
        buffer[threadNum][i++]=ch;
    }

    buffer[threadNum][i]='\0';
    printf("Contents read from %s:\n%s\n",fileName,buffer[threadNum]);
    printf("Thread number %d with ID %ld is exiting\n",threadNum+1,pthread_self());
    close(file);
    pthread_exit(NULL);
}

int main(int argc,char*argv[])
{
    if(argc<2)
    {
        printf("Error! atleast one argumennts needed: <namedPipe>\n");
        return 0;
    }

    pthread_t threadsArr[max_threads];
    threadArg threadArgArr[max_threads];
    int flag=0;

    int pipe= open(argv[1],O_RDWR);

    if(pipe==-1)
    {
        printf("Named pipe failed to open\n");
        return 0;
    }

    while(1)
    {
        int totalThreads;
        printf("\nWaiting for client...\n");
        if(flag==0)
        {
            flag=1;
        }
        else
        {
            sleep(totalThreads+2);
        }

        int size;
        read(pipe,&size,sizeof(int));
        totalThreads=size;
        
        for(int i=0;i<totalThreads;i++)
        {
            read(pipe,&size,sizeof(int));
            read(pipe,buffer[i],size);
            buffer[i][size]='\0';
            printf("Received File name: %s\n",buffer[i]);
            threadArgArr[i].threadNum=i;
            pthread_create(&threadsArr[i],NULL,worker,(void*)&threadArgArr[i]);
        }
        
        for(int j=0;j<totalThreads;j++)
        {
            pthread_join(threadsArr[j],NULL);
        }

        printf("Sending file contents to client\n");
        for(int j=0;j<totalThreads;j++)
        {
            size=strlen(buffer[j]);
            write(pipe,&size,sizeof(int));
            write(pipe,buffer[j],size);
        }
    }
    close(pipe);
    return 0;
}