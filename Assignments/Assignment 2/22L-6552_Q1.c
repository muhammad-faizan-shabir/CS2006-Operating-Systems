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

void* findMax(void *param)
{
    ArrayData * Obj= (ArrayData*)param;
    int max=Obj->Arr[0];
    
    for(int i =1;i<Obj->size;i++)
    {
        if(Obj->Arr[i]>max)
        {
            max=Obj->Arr[i];

        }
    }
    pthread_exit((void*)(intptr_t)max);
}

void*findMin(void * param)
{
    ArrayData * Obj= (ArrayData*)param;
    int min=Obj->Arr[0];
    
    for(int i =1;i<Obj->size;i++)
    {
        if(Obj->Arr[i]<min)
        {
            min=Obj->Arr[i];

        }
    }
    pthread_exit((void*)(intptr_t)min);
}

int main(int argc,char*argv[])
{
    if(argc<2)
    {
        printf("Error! Atleast Pass One Number as Parameter\n");
        return 0;
    }

    int SizeOfArr= argc-1;
    int Arr[Max_Array_Length];

    for(int i=0;i<SizeOfArr;i++)
    {
        Arr[i]= atoi(argv[i+1]);
    }

    ArrayData Object1;
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

    pthread_t maxThread;
    pthread_create(&maxThread,NULL,findMax,&Object1);
    
    pthread_t minThread;
    pthread_create(&minThread,NULL,findMin,&Object1);
    
    void* avg;
    pthread_join(avgThreadID,&avg);

    void*max;
    pthread_join(maxThread,&max);

    void*min;
    pthread_join(minThread,&min);
    
    printf("The Average is: %d\n",(int)(intptr_t)avg);
    printf("The max value is: %d\n",(int)(intptr_t)max);
    printf("The min value is: %d\n",(int)(intptr_t)min);

    return 0;
}
