#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct{
long int mssg_type;
char mssg[BUFSIZ];
} data;


int palin(char str[]){
int end=strlen(str)-1;
for(int i=0;i<=strlen(str)/2;i++){
if(str[i]!=str[end-i-1]) return 0;
}
return 1;


}
int main(){
data d;
int running=1;

int mssgid;
long int msg_to_receive = 0;
mssgid=msgget((key_t)1111, 0666 | IPC_CREAT);
if(mssgid==-1){
fprintf(stderr, "msgget failed with error: %d\n", errno);
exit(0);
}
while(running){
if(msgrcv(mssgid, (void*)& d, BUFSIZ,msg_to_receive,0)==-1){
printf("mssg send error\n");
exit(0);
}
printf("received data is %s", d.mssg);
if(palin(d.mssg)) printf("palin\n");
else printf("not palin\n");
if(strcmp(d.mssg, "end")==0) running=0;
}
printf("rcv prgm end\n");



}
