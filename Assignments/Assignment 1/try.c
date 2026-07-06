#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
int main(int argc, char *argv[])
{
    int digits=0;
    int TotalSections=argc-2;
    int fd[2];
    int fd2[2];
    pipe(fd);
    pipe(fd2);
    pid_t pid;
    int studentsFile=open(argv[1],O_RDONLY);
    if(studentsFile==-1)
    {
        char*fileError="Students file not opened!\n";
        write(1,fileError,strlen(fileError));
        return 0;
    }
    
    int totalStudents=0;
    
    char buffer[19];

    for(int i=1;i<=3;i++)
    {
        //pid = fork();
        for(;read(studentsFile,buffer,19)>0;)
        {
            printf("%s",buffer);
        }
        lseek(studentsFile,2,SEEK_SET);

        
    }
    close(studentsFile);

    return 0;
}