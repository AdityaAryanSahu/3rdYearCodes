#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
int n;
int pd[2];
pipe(pd);
char buffer[1024];
char *data="AdityaAryanSahuXD";
write(pd[1], data, strlen(data));
if((n=read(pd[0], buffer, 1023))>0){
buffer[n]='\0';
printf("read %d bytes and read data is %s\n", n, buffer);
}
else{
printf("error\n");
}
printf("done\n");
}
