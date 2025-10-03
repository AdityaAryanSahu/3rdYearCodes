#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void* gen_fib(void*param){
 int num=(int) param;
 printf("num: %d\n",num);
 int* arr=(int*)calloc(num,sizeof(int));
 if(arr==NULL) printf("mem all error\n");
 int count=2;
int i=0,j=1;
arr[0]=0;
arr[1]=1;
while(count<num){
arr[count]=arr[count-1]+arr[count-2];
count++;
}

return (void*)arr;
}

int main(){
int num;
printf("enter a number\n");
scanf("%d",&num);
int *res;
pthread_t pth;
pthread_create(&pth,0,&gen_fib, (void*)num);
pthread_join(pth, (void**)&res);
for(int i=0;i<num;i++) printf("%d\n",res[i]);
return 0;
}
