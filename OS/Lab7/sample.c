#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/ipc.h>
#define max_text 1024

typedef struct{
long int mssg_type;
char mssg[max_text];
} data;

int main(){
data d;
int running=1;
char buffer[BUFSIZ];

int mssgid;
mssgid=msgget((key_t)1234, 666 | IPC_CREAT);
if(mssgid==-1){
printf("error in mmsgid\n");
exit(0);
}
while(running){
printf("enter some text:\n");
gets(buffer);
strcpy(d.mssg, buffer);
d.mssg_type=1;
if(msgsnd(mssgid,(void*)& d, max_text, 0)==-1){

printf("mssg send error\n");
exit(0);
}

if(strcmp(buffer, "end")==0) running=0;
}
printf("sender prgm end\n");



}
