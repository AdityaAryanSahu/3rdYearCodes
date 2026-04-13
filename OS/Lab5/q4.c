#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main(){
pid_t pid=fork();
if(pid==-1){
printf("dead\n");
exit(1);
}
else if(pid==0){
printf("cjild\n");
exit(1);
}
else{
printf("parent\n");
}
execlp("/bin/ps", "ps", NULL);
}
