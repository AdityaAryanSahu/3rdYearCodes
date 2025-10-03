#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
char *data="hahaha";
char buffer[1024];
int n, pf;
if(access("fifo",F_OK)==-1){
int res=mkfifo("fifo",777);
if(res==0){
printf("fifo created\n"); 
   }
}
printf("Process %d opening FIFO O_WRONLY\n", getpid());
pf=open("fifo", O_RDWR);
printf("Process %d result %d\n", getpid(), pf);
if(pf==-1) printf("pf error\n");
n=write(pf, data, strlen(data));
if(n!=-1) printf("write successful\n");
else printf("tmkc\n");

close(pf);
printf("done\n");
}
