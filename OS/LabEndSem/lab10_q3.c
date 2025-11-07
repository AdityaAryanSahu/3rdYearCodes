#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<semaphore.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<pthread.h>
#define size 5


// segment table etc using thread+semaphore
typedef struct{
    int base;
    int limit;
}segment;

typedef struct{
    segment table[5];
    int off;
    int id;
}shm;

sem_t lock;

void create_table(segment table[]){
    for(int i=0;i<5;i++){
        table[i].base=(i*1000);
        table[i].limit=2000;
    }
    printf("semne ttable created\n");
}
int logtophy(segment table[],int id, int off){
    
    return off>table[id].limit? -1: (table[id].base+off);
}

void * func1(void* arg){
    sem_wait(&lock);
    shm* sm=(shm*)arg;
    create_table(sm->table);
    sem_post(&lock);
}
void* func2(void* arg){
    sem_wait(&lock);
    int off,id;
    shm* sm=(shm*)arg;
    printf("enter off and id\n");
    scanf("%d%d",&off,&id);
    int res=logtophy(sm->table,id,off);
    if(res!=-1){
        printf("%d done\n", res);

    }
    else printf("Laude lag gaye\n");
    sem_post(&lock);
}

int main(){
    sem_init(&lock,0,1);
    pthread_t t1,t2,t3;
    int id=shmget((key_t)1234,sizeof(shm), 0666|IPC_CREAT);
    shm* sm=(shm*)shmat(id,NULL,0);
    pthread_create(&t3,0,func1,(void*)sm);
    
    pthread_create(&t1,0,func2,(void*)sm);
    
    pthread_create(&t2,0,func2,(void*)sm);
    pthread_join(t3,0);
    pthread_join(t1,0);
    pthread_join(t2,0);

}