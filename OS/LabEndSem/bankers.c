#include<sys/shm.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define P 5
#define R 3

int total[R] = {10, 10, 10};
int max[P][R], need[P][R], allocated[P][R];
int available[R],work[R];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

int isSafe(){
    int count=0;
    int finished[P];
    for(int i=0;i<P;i++) finished[i]=0;
    for(int i=0;i<R;i++) work[i]=available[i];

    while(count<P){
        int done=0;
        for(int i=0;i<P;i++){
            if(!finished[i]){
                int canAlloc=1;
            for(int j=0;j<R;j++){
                if(need[i][j]>work[j]){
                    canAlloc=0;
                    break;
                }
            }
            if(canAlloc){
                finished[i]=1;
                for(int a=0;a<R;a++) work[a]+=allocated[i][a];
                count++;
                done=1;
           }
        }
    }
    if(!done) return 0;
    }
return 1;
}


void * process(void* arg){
    int p=*(int*)arg;
    pthread_mutex_lock(&mutex);
    for(int j=0; j<R; j++) 
    {
        available[j] -= need[p][j];
        allocated[p][j] += need[p][j];
        need[p][j] = 0;
    }
    if(isSafe()){ 
        printf("safe\n");
        pthread_mutex_unlock(&mutex);
        sleep(1); // simulate processing time

        pthread_mutex_lock(&mutex);
        for(int j=0; j<R; j++) {
            available[j] += allocated[p][j];
            allocated[p][j] = 0;
        }
    }
    else {
         for(int j=0; j<R; j++) {
            need[p][j] = max[p][j];
            allocated[p][j] = 0;
            available[j] = total[j]; 
        }
        printf("\nRequest denied for P%d (would lead to unsafe state).\n", p);
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
        for(int i=0;i<R;i++) available[i]=total[i];

        printf("Enter Max matrix (5x3):\n");
        for (int i = 0; i < P; i++) {
            for (int j = 0; j < R; j++) {
                scanf("%d", &max[i][j]);
                allocated[i][j] = 0;
                need[i][j] = max[i][j];
        }
    }
    for(int i=0;i<R;i++) available[i]=total[i];
    pthread_t th[5];
    for(int i=0;i<5;i++){
        pthread_create(&th[i],0,process,(void*)&i);
    }
    for(int i=0;i<5;i++){
        pthread_join(th[i],0);
    }
}