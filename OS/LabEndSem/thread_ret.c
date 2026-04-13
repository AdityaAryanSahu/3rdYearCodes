#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int n;

// to retrun int convert int to int* then cast void*
// to convert void* to int, cast to int* then derefernce *


void * th1(void * arg){
    int * arr=(int *)arg;
int *sum=malloc(sizeof(int));
     *sum=0;
    for(int i=0;i<n;i++) *sum+=arr[i];
    return (void*) sum;
}

void * th2(void * arg){
    int num=*(int*)arg;
    int *is_even = malloc(sizeof(int));
    *is_even = (num % 2 == 0) ? 1 : 0;
    return (void*) is_even;
}

int main(){
    pthread_t t1,t2;
    n=5;
    int m=10;
    int arr[n];
    for(int i=0;i<5;i++) scanf("%d",&arr[i]);
    pthread_create(&t1,0,th1,(void*)arr);
    pthread_create(&t2,0,th2,(void*)&m);
    printf("thread created\n");
    int *res;
    int *res2;
    pthread_join(t1,(void**)&res);
    pthread_join(t2,(void**)&res2);
    printf("th1: %d\n th2: %d\n",*res, *res2);
}