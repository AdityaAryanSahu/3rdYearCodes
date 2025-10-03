#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
char buffer[1024];
int n, pf;
printf("Process %d opening FIFO O_RDONLY\n", getpid());
pf=open("fifo", O_RDONLY);
printf("Process %d result %d\n", getpid(), pf);
if(pf==-1) printf("pf error\n");
n=read(pf, buffer, 1023);
puts(buffer);
if(n!=-1) printf("\nread successful\n");
else printf("tmkc\n");

close(pf);
printf("done\n");
}
