#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
int m;
void * thr(void *nums){
int sum=0;
int *arr=(int*)nums;
for(int i=0;i<m;i++){
if(arr[i]<0) continue;
sum+=arr[i];
}

return (void*)sum;
}

int main(){
printf("enter a size\n");
scanf("%d",&m);
int arr[m];
printf("enter array\n");
for(int i=0;i<m;i++) scanf("%d",&arr[i]);
int sum;
pthread_t th;
pthread_create(&th,0,&thr,(void*)arr);
pthread_join(th,(void**)&sum);
printf("sum: %d\n",sum);

}
