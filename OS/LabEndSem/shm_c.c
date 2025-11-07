#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include "shm.h"

int main(){
    int id=shmget((key_t)1234, sizeof(shm),0666|IPC_CREAT);
    shm* sm=(shm*)shmat(id, NULL,0);
    while(1){
        while(sm->type!=1);
        printf("got data\n");
        puts(sm->data);
        sm->type=2;
    }
}