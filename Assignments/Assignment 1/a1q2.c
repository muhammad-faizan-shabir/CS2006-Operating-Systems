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
    int pipe1[2];
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    pid_t pid;
    int studentsFile=open(argv[1],O_RDONLY);
    if(studentsFile==-1)
    {
        char*fileError="Students file not opened!\n";
        write(1,fileError,strlen(fileError));
        return 0;
    }
    
    int totalStudents=0;
    char ch[1];
    read(studentsFile,ch,1);
    while(ch[0]!='\n')
    {
        digits++;
        totalStudents = (totalStudents*10)+((*ch)-48);
        read(studentsFile,ch,1);
    }

    for(int l=1;l<=TotalSections;l++)
    {
        pid = fork();

        if(pid<0)
        {
            char*forkError="Fork failed\n";
            write(1,forkError,strlen(forkError));
            exit(EXIT_FAILURE);
        }
        else if(pid==0)
        {
            close(pipe1[1]);
            close(pipe2[1]);
            int sectionFile=open(argv[l+1],O_WRONLY);
            if(sectionFile==-1)
            {
                char*errorSectionfile="Section file not opening!\n";
                write(1,errorSectionfile,strlen(errorSectionfile));
                exit(EXIT_FAILURE);
            }

            int currSecCount;
            read(pipe1[0],&currSecCount,4);
            char buffer2[19];
            for(int k=1;k<=currSecCount;k++)
            {
                read(pipe2[0],buffer2,19);
                buffer2[13]='\n';
                write(sectionFile,buffer2,14);
            }

            printf("Child ID: %d Parent ID: %d\n",getpid(),getppid());

            close(sectionFile);
            close(pipe1[0]);
            close(pipe2[0]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(pipe1[0]);
            close(pipe2[0]);
            int secCount=0;
            char buffer[19];
            for(int j=1;j<=totalStudents;j++)
            {
                read(studentsFile,buffer,19);
                if((buffer[17]-48)==l)
                {
                    write(pipe2[1],buffer,19);
                    secCount++;
                }
            }
            write(pipe1[1],&secCount,4);
            wait(NULL);
            lseek(studentsFile,digits+1,SEEK_SET);
        }
    }
    close(studentsFile);

    return 0;
}
