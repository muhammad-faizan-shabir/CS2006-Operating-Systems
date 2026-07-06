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
    int studentsFile;
    char arr[1000][19];
    char buffer[19];
    int ctr=0;
    


    studentsFile=open(argv[1],O_RDWR);
            
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
    printf("%d\n",TotalSections);

    for(int i=0;i<=totalStudents;i++)
    {
        read(studentsFile,buffer,19);
        for(int j=0;j<19;j++)
        {
            arr[ctr][j]=buffer[j];
        }
        ctr++;
    }
          

    for(int i=1;i<=TotalSections;i++)
    {
        printf("g\n");
        pid =1;//fork();

        if(pid<0)
        {
            char*forkError="Fork failed\n";
            write(1,forkError,strlen(forkError));
            exit(EXIT_FAILURE);
        }
        else if(pid==0)
        {
            printf("h\n");
            close(fd[1]);
            close(fd2[1]);
            int sectionFile=open(argv[i+1],O_RDWR);
            if(sectionFile==-1)
            {
                char*errorSectionfile="Section file not opening!\n";
                write(1,errorSectionfile,strlen(errorSectionfile));
                exit(EXIT_FAILURE);
            }

            int currSecCount;
            read(fd[2],&currSecCount,sizeof(int));
            
            char buffer2[19];
            for(int k=1;k<=currSecCount;k++)
            {
                read(fd[0],buffer2,19);
                buffer2[13]='\n';
                write(sectionFile,buffer2,14);
                //write(1,buffer2,14);
            }

            //printf("Child ID: %d Parent ID: %d",getpid(),getppid());
            

            

            close(sectionFile);
            close(fd[0]);
            close(fd2[0]);
            exit(0);
            //return 0;
        }
        else
        {
             
            close(fd[0]);
            close(fd2[0]);
            int secCount=0;
            for(int j=0;j<totalStudents;j++)
            {
                
                //if((arr[j][17]-48)==i)
                //{
                write(1,arr[j],19);
                    //secCount++;

                //}

            }
            
            

            write(fd2[1],&secCount,4);
            wait(NULL);
        }
        if(pid==0)
        {
            exit(0);
        }
    }
    //close(studentsFile);

    return 0;
}