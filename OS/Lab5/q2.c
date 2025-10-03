#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main(){
pid_t pid=fork();
if(pid==-1){
printf("doesnt work sadly\n");
exit(0);
}
else if(pid==0){
printf("child created :(\n");
execlp("./q1", "q1", NULL);
exit(0);
}
else{
wait(NULL);
printf("parent done \n");
exit(1);
}
printf("program done\n");
}
