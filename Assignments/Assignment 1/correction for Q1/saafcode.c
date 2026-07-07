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
    char ch[1];
    read(studentsFile,ch,1);
    while(ch[0]!='\n')
    {
        digits++;
        totalStudents = (totalStudents*10)+((*ch)-48);
        read(studentsFile,ch,1);
    }
    

    for(int i=1;i<=TotalSections;i++)
    {
        pipe(fd);
        pipe(fd2);
        
        pid = fork();

        if(pid<0)
        {
            char*forkError="Fork failed\n";
            write(1,forkError,strlen(forkError));
            exit(EXIT_FAILURE);
        }
        else if(pid==0)
        {
            close(fd[1]);
            close(fd2[1]);
            int sectionFile=open(argv[i+1],O_WRONLY);
            if(sectionFile==-1)
            {
                char*errorSectionfile="Section file not opening!\n";
                write(1,errorSectionfile,strlen(errorSectionfile));
                exit(EXIT_FAILURE);
            }
            printf("Child ID : %d Parent ID %d\n",getpid(),getppid());

            int currSecCount;
            read(fd[2],&currSecCount,4);
            char buffer2[19];
            for(int k=1;k<=currSecCount;k++)
            {
                read(fd[0],buffer2,19);
                buffer2[13]='\n';
                write(sectionFile,buffer2,14);
            }

            close(sectionFile);
            //close(fd[0]);
            //close(fd2[0]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(fd[0]);
            close(fd2[0]);
            int secCount=0;
            char buffer[19];
            for(int j=1;j<=totalStudents;j++)
            {
                read(studentsFile,buffer,19);
                if((buffer[17]-48)==i)
                {
                    write(fd[1],buffer,19);
                    secCount++;
                }
            }
            write(fd2[1],&secCount,4);
            //close(fd2[1]);
            //close(fd[1]);
            wait(NULL);
            lseek(studentsFile,0,SEEK_SET);
            read(studentsFile,ch,1);
            while(ch[0]!='\n')
            {
                read(studentsFile,ch,1);
            }
        }
    }
    close(studentsFile);

    return 0;
}
