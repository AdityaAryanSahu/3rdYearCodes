#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#define name "/home/chief_ramos/os_labendsem/my_fifo"

int main(){

    char data[1024];
    int pid=open(name, O_RDONLY);
    if(pid>0){
        int x=read(pid, data, 1024);
        data[x]='\0';
        puts(data);
    }
    close(pid);
    return 0;

}