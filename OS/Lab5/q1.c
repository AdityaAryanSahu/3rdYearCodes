#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(){
pid_t pid=fork();
if(pid==-1){
printf("hahah lol\n");
}
else if(pid==0){
printf("sadly works\n");
exit(1);
}
else{
wait(NULL);
printf("parent entered\n");
exit(0);
}
}
