#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
int m;
//th1 odd
void * th1(void *nums){
int sum1=0;
int *arr=(int*)nums;

for(int i=0;i<m;i++){
if(arr[i]%2==0) continue;
sum1+=arr[i];
}
printf("thread 1 exit with sum %d\n",sum1);
int *ret = malloc(sizeof(int));
    if (!ret) pthread_exit(NULL);
    *ret = sum1;
    return ret;

}
//th2 even
void * th2(void *nums){
int sum=0;
int *arr=(int*)nums;
for(int i=0;i<m;i++){
if(arr[i]%2!=0) continue;
sum+=arr[i];
}
printf("thread 2 exit\n");
int *ret = malloc(sizeof(int));
    if (!ret) pthread_exit(NULL);
    *ret = sum;
    return ret;

}

int main(){
printf("enter a size\n");
scanf("%d",&m);
int arr[m];
printf("enter array\n");
for(int i=0;i<m;i++) scanf("%d",&arr[i]);
int *sum1,*sum2;
pthread_t thr1,thr2;
pthread_create(&thr1,0,&th1,(void*)arr);
pthread_create(&thr2,0,&th2,(void*)arr);
pthread_join(thr1,(void**)&sum1);
pthread_join(thr2,(void**)&sum2);
printf("odd_sum: %d\neven_sum: %d\n",*sum1,*sum2);
}
