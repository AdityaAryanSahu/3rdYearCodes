#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
int count=0;
sem_t mut1, mut2;

void* th1(void*arg){

sem_wait(&mut1);
sleep(1);
count++;
printf("th1 with count: %d\n",count);
sem_wait(&mut2);
sem_post(&mut2);
sem_post(&mut1);
}


void* th2(void* arg){


sem_wait(&mut2);
sleep(1);
count--;
printf("th2 with count: %d\n",count);
sem_wait(&mut1);


sem_post(&mut1);
sem_post(&mut2);
}

void main(){
pthread_t tid1, tid2;
sem_init(&mut1,0,1);
sem_init(&mut2,0,1);
pthread_create(&tid1,NULL,th1,NULL);
pthread_create(&tid2,NULL,th2,NULL);
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
}
