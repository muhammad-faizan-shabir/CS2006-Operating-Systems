#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
int main(int argc, char *argv[])
{
    //printf("g\n");
    int digits=0;

    int TotalSections= argc-2;
    int fd[2];
    int fd2[2];
    pipe(fd);
    pipe(fd2);
    pid_t pid;
    //printf("g\n");
    const char*mainFile=argv[1];
    //printf("g\n");
    int studentsFile= open(mainFile,O_RDONLY);
    //printf("g\n");
    if(studentsFile==-1)
    {
        //printf("g\n");
        char*fileError="Students file not opened!\n";
        write(1,fileError,strlen(fileError));
        return 0;
    }
    //printf("g\n");
    char ch[2];
    int totalStudents=0;
    /*read(studentsFile,ch,1);
    //printf("%s\n",ch);
    while((*ch)!='\n')
    {
        digits++;
        totalStudents = (totalStudents*10)+((*ch)-48);
        read(studentsFile,ch,1);
        //printf("g\n");

    }*/
    //printf("%d\n",digits);
    //printf("%d\n",TotalSections);
    

    for(int i=1;i<=TotalSections;i++)
    {
        //printf("g\n");
        pid= fork();

        if(pid<0)
        {
            char*forkError="Fork failed\n";
            write(1,forkError,strlen(forkError));
            exit(EXIT_FAILURE);
        }
        else if (pid==0)
        {
            close(fd[1]);
            close(fd2[1]);
            const char*secFile=argv[i+1];
            int sectionFile =open(secFile,O_WRONLY);
            if(sectionFile==-1)
            {
                char*errorSectionfile="Section file not opening!\n";
                write(1,errorSectionfile,strlen(errorSectionfile));
                exit(EXIT_FAILURE);
            }
            int currSecCount;
            read(fd2[0],&currSecCount,4);
            printf("%d\n",currSecCount);
            char buffer2[19];
            
            int count=0;
            for(int k=1;i<=currSecCount;k++)
            {
                read(fd[0],buffer2,19);
                buffer2[13]='\n';
                write(sectionFile,buffer2,14);
            }
            //close(sectionFile);
            printf("g\n");
            //printf("%ld\n",k);
            close(studentsFile);

            exit(EXIT_SUCCESS);
            

            

        }
        else
        {
            close(fd[0]);
            close(fd2[0]);
            int currSecCount=0;
            char ch2[2];

            char buffer[20];
            for(;read(studentsFile,buffer,19)>0;)
            {
                //read(studentsFile,buffer,19);
                //printf("%s",buffer);
                //printf("%d\n",(buffer[17]-48));
                if((buffer[17]-48)==i)
                {

                    printf("%d\n",(buffer[17]-48));
                    write(fd[1],buffer,19);
                    currSecCount++;
                }
            }
            write(fd2[1],&currSecCount,4);
            printf("%d\n",currSecCount);
            //close(studentsFile);
            wait(NULL);
            
            //studentsFile= open(mainFile,O_RDONLY);
            lseek(studentsFile,0,SEEK_SET);
            //sleep(2);
            //read(studentsFile,ch,1); 
            //printf("%s\n",ch);           
            //while((ch[0])!='\n')
            //{
                //read(studentsFile,ch,1);
               //printf("%s",ch);
            //}

        }

    }

    close(studentsFile);



    return 0;


}

