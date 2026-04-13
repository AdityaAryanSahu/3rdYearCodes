#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main(){
pid_t pid=fork();
if(pid==-1){
printf("sad you messed up\n");
exit(0);
}
else if(pid==0){
printf("for child\nchilds id: %d, parents id: %d\n", getpid(), getppid());
exit(1);
}
else{
wait(NULL);
printf("for parent\nchilds id: %d, parents id: %d\n", getpid(), getppid());
}
}
