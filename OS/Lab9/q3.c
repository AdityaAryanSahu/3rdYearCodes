#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int m, n;
int prime(int num){
int lim= (int)sqrt(num);
for(int i=2;i<=lim;i++){
if(num%i==0) return 0;
}
return 1;
}

void* gen_pri(void*param){

int i=0;
for(i=m;i<n;i++){
if(prime(i)) printf("%d is prime\n",i);
}

}

int main(){
printf("enter a lower and upper limit\n");
scanf("%d%d",&m,&n);
pthread_t pth;
pthread_create(&pth,0,&gen_pri, 0);
pthread_join(pth, 0);
return 0;
}
