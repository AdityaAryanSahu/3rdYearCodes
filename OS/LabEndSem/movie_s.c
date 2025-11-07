#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/msg.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<string.h>
#include<math.h>
typedef struct {
    char name[1024];
    int cost;
    int count;
    int id;
}movie;

int main(){
    movie mov;
    int id=msgget((key_t)1234,0666|IPC_CREAT);
    if(id>0){
        printf("enter details:\n");
        scanf("%s%d%d", mov.name, &mov.cost, &mov.count);
        mov.id= 1234444;
        int x=msgsnd(id,(void*)&mov, sizeof(mov), 0);
    }
}