#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include "shm1.h"

sem_t lock, seat;
int n=0;
void * func(void * arg){
    shm* sm=(shm*)arg;
    sem_wait(&lock);
    if(sm->seats>0){
        sm->seats--;
        n++;
        printf("counter %d booked. Reamaining: %d\n", n, sm->seats);
    }
    else printf("no seats\n");
    sem_post(&lock);
}


int main(){
    pthread_t t1,t2,t3;
    int id=shmget((key_t)1234, sizeof(shm), 0666|IPC_CREAT);
    shm* sm=(shm*)shmat(id,NULL,0);
    sm->seats=5;
    sm->type=0;
    sem_init(&lock,0,1);
    pthread_create(&t1,0,func,(void*)sm);
    pthread_create(&t2,0,func,(void*)sm);
    pthread_create(&t3,0,func,(void*)sm);
    pthread_join(t1,0);
    pthread_join(t2,0);
    pthread_join(t3,0);
    return 0;



}

