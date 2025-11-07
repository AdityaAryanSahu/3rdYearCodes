#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

pthread_mutex_t mutex;
sem_t lock;
int count=0;

/*
mutex intitialization & functions

pthread_mutex_init(&mutex,0); or mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&mutex);
pthread_mutex_unlock(&mutex);

*/


void * fuc(void *arg){


while(count<10){
sem_wait(&lock);
count++;
printf("count increment: %d\n", count);
sem_post(&lock);
}

}

int main(){
    pthread_t t1,t2,t3;
    sem_init(&lock, 0,1);
    pthread_create(&t1,0,fuc,0);
    pthread_create(&t2,0,fuc,0);
    pthread_create(&t3,0,fuc,0);
    pthread_join(t1,0);
    pthread_join(t2,0);
    pthread_join(t3,0);

}