#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

int count=0;
sem_t mutex,wrt;
void *writer(void*arg){
int i=0;
do{
wait(wrt);
printf("writer %d wrote\n",i++);
sleep(2);
signal(wrt);
}while(1);
}

void *reader(void*arg){
int i=0;
do{
wait(mutex);
count++;
if(count==1) wait(wrt);
signal(mutex);
printf("reader %d read\n",i++);
wait(mutex);
sleep(2);
count--;
if(count==0) signal(wrt);
signal(mutex);
}while(1);
}

int main(){
pthread_t tid1,tid2;
sem_init(&mutex,0,1);
sem_init(&wrt,0,1);
pthread_create(&tid1,NULL,writer,NULL);
pthread_create(&tid2,NULL,reader,NULL);
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);

}
