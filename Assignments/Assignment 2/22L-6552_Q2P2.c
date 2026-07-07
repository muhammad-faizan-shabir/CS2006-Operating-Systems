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

int main(int argc,char*argv[])
{
    if(argc<3)
    {
        printf("Error! atleast two arguments needed: <namedPipe> <file name>\n");
        return 0;
    }

    int pipe= open(argv[1],O_RDWR);
    int size;

    if(pipe==-1)
    {
        printf("Named pipe failed to open\n");
        return 0;
    }

    printf("Got filename(s): ");
    for(int i=2;i<argc;i++)
    {
        printf("%s ",argv[i]);
    }
    printf("from commandline\n");
    printf("Sending filename(s) to server\n");

    size=argc-2;
    write(pipe,&size,sizeof(int));

    for(int i=2;i<argc;i++)
    {
        size =strlen(argv[i]);
        write(pipe,&size,sizeof(int));
        write(pipe,argv[i],size);
    }
    
    char buffer[1000];
    printf("Waiting for server to respond...\n\n");
    sleep(argc-2);

    for(int i=2;i<argc;i++)
    {
        read(pipe,&size,sizeof(int));
        read(pipe,buffer,size);
        buffer[size]='\0';
        printf("Contents of %s from pipe:\n%s\n",argv[i],buffer);
    }
    return 0;
}
