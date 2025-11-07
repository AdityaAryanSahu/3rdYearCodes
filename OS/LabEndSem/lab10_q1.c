#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define num_block 5


// easier verison of lab10q1 using threads

pthread_mutex_t mutex;

typedef struct{
    int id;
    int size;
    int allocated;
}block;

block Block_table[num_block];


void * best_fit(void *arg){
    pthread_mutex_lock(&mutex);
     printf("---------------Best fit---------------");
    int size=*(int *)arg;
    int min_idx=-1;;
    for(int i=0;i<num_block;i++){
        if(!Block_table[i].allocated && Block_table[i].size>=size){
            if(min_idx==-1 || Block_table[i].size<Block_table[min_idx].size)
            min_idx=i;
        }
    }
    Block_table[min_idx].allocated=1;
    printf("for requested size: %d, gave block %d\n",size,min_idx);
    pthread_mutex_unlock(&mutex);

}
void * first_fit(void *arg){
    pthread_mutex_lock(&mutex);
    printf("---------------first fit---------------");
    int size=*(int *)arg;
    for(int i=0;i<num_block;i++){
        if(!Block_table[i].allocated && Block_table[i].size>=size){
            printf("for requested size: %d, gave block %d\n",size,i);
            Block_table[i].allocated=1;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
    
    pthread_mutex_init(&mutex,0);
    int size;
    pthread_t threads[1024];
    int i=0;
    printf("enter blobk details\n");
    for(int i=0;i<num_block;i++){
        scanf("%d", &Block_table[i].size);
        Block_table[i].id=i;
        Block_table[i].allocated=0;
    }
    while(1){
    printf("enter request size\n");
    scanf("%d",&size);
    int * sz=(int *)malloc(sizeof(int));
    *sz=size;
    pthread_create(&threads[i],0,first_fit,(void*)sz);
    pthread_join(threads[i],0);
    pthread_create(&threads[i],0,best_fit,(void*)sz);
    pthread_join(threads[i],0);
    i++;
    free(sz);
    }
    return 0;



}