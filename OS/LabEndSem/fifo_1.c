#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<string.h>
#include <stdlib.h>
#include<fcntl.h>
#define name "/home/chief_ramos/os_labendsem/my_fifo"


int main(){

int pid;
char * data="hi fifo question";
if(mkfifo(name, 0777)==-1){}

pid=open(name, O_WRONLY);
if(pid!=-1){
    int x=write(pid, data, sizeof(data));
    if(x<0) printf("error in sending\n");
}
close(pid);
return 0;

}