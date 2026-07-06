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
#define Max_Array_Length 100

typedef struct
{
    int * Arr;
    int size;
} ArrayData;

void * calulateAvg(void * param)
{
    ArrayData * Obj= (ArrayData*)param;
    int avg;
    int sum=0;

    for(int i =0;i<Obj->size;i++)
    {
        sum+=Obj->Arr[i];
    }

    avg=sum/Obj->size;

    pthread_exit((void*)(intptr_t)avg);

}

int main(int argc,char*argv[])
{
    if(argc<2)
    {
        printf("Error! Atleast Pass One Number as Parameter\n");
        return 0;
    }
    ArrayData Object1;


    int SizeOfArr= argc-1;
    int Arr[Max_Array_Length];

    for(int i=0;i<SizeOfArr;i++)
    {
        Arr[i]= atoi(argv[i+1]);
    }
    Object1.Arr=Arr;
    Object1.size=SizeOfArr;

    printf("The input array is: ");

    for(int i=0;i<SizeOfArr;i++)
    {
        printf("%d ",Arr[i]);
    }

    printf("\n");

    pthread_t avgThreadID;

    pthread_create(&avgThreadID,NULL,calulateAvg,(void *)&Object1);
    void* avg;

    pthread_join(avgThreadID,&avg);

    printf("The Average is: %d\n",(int)(intptr_t)avg);


    



}