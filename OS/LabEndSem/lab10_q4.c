#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
#define frame_size 3
#define page_size 10


// LRU second chance algo

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
typedef struct{
    int page;
    int refbit;
}Frame;

typedef struct{
Frame frames[frame_size];
int page[page_size];
int n;
int completed;
}shm;
int pagefault=0;

void * sec_chance(void *arg){
    shm* sm=(shm*)arg;
    int count=0;
    int next=0;
    for(int i=0;i<sm->n;i++){
        pthread_mutex_lock(&mutex);
        int found=0;
        for(int j=0;j<frame_size;j++){
            if(sm->frames[j].page==sm->page[i]){
                  sm->frames[j].refbit=1;
                  found=1; 
                  break;  
            }
        }
        if(!found){
            pagefault++;
            while(1){
                if(sm->frames[next].refbit==0){
                    sm->frames[next].refbit=1;
                    sm->frames[next].page=sm->page[i];
                    next=(next+1)%frame_size;
                    break;
                }
                else{
                    sm->frames[next].refbit=0;
                    next=(next+1)%frame_size;
                }
            }
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    sm->completed=1;
}
void * display(void * arg){
    shm* sm=(shm*)arg;
    while(!sm->completed){
    pthread_mutex_lock(&mutex);
    printf("\nFrames: ");
    for(int i=0;i<frame_size;i++){
        if(sm->frames[i].page==-1) printf("- ");
        else printf("%d ",sm->frames[i].page);
    }
    printf(" | Page Faults: %d", pagefault);
    pthread_mutex_unlock(&mutex);
    sleep(1);
    }
}
int main(){
    int id=shmget((key_t)1234,sizeof(shm), 0666|IPC_CREAT);
    shm* sm=(shm*)shmat(id,NULL,0);
    pthread_t t1,t2;

    for(int i=0;i<frame_size;i++){
        sm->frames[i].page=-1;
        sm->frames[i].refbit=0;
    }
    sm->completed=0;
    printf("number of pages\n");
    scanf("%d",&sm->n);
    printf("sequence pf pages\n");
    for(int i=0;i<sm->n;i++){
        scanf("%d",&sm->page[i]);
    }
    pthread_create(&t1,0,sec_chance,(void*)sm);
    pthread_create(&t2,0,display,(void*)sm);
    pthread_join(t1,0);
    pthread_join(t2,0);
}