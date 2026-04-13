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
    int id=msgget((key_t)1234, 0666|IPC_CREAT);
    movie mov;
    if(id>0){
        int y=msgrcv(id,(void*)&mov, sizeof(mov), (long int)0, 0);
        printf("%s %d %d %d\n", mov.name, mov.cost,mov.count, mov.id);
        printf("\nbill:\n");
        printf("%.2f", (double)(mov.count*mov.cost));
    }
    return 0;
}