#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#define PIPE_PERM (S_IRUSR|S_IWUSR)
int main(int argc,char*argv[])
{
    char*pipe_name=argv[1];
    int status=mkfifo(pipe_name,PIPE_PERM);
    printf("%d\n",status);
    return 0;
}