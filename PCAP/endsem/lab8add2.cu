#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__device__ int fact(int n){
    if(n==0 || n==1) return 1;
    int res=1;
    while(n>1){
        res*=n;
        n--;
    }
    return res;
}

__device__ int sum(int n){
    if(n<10) return n;
    int sum=0;
    while(n>0){
        sum+=n%10;
        n/=10;
    } 
    return sum;
}

__global__ void calc(int *a, int n){
    int col = blockDim.x*blockIdx.x+threadIdx.x;
    int row = blockDim.y*blockIdx.y+threadIdx.y;

    if(col<n && row<n){
        int num=a[row*n+col];
        if(col == row) a[row*n+col]=0;
        else if(row>col) a[row*n+col]=sum(num);
        else a[row*n+col]=fact(num);
    }
}

int main(){
    int n;
    printf("enter dim n\n");
    scanf("%d",&n);

    int a[n*n];

    printf("enter array a\n");
    for(int i=0;i<n*n;i++) scanf("%d", &a[i]);

    int size = n*n*sizeof(int);
    int *d_a;
    cudaMalloc((void**)&d_a, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    dim3 grid(1,1,1);
    dim3 block(n,n,1);

    calc<<<grid, block>>>(d_a,n);
    cudaMemcpy(a, d_a, size, cudaMemcpyDeviceToHost);

    for(int i=0;i<n*n;i++){
       if(i%n == 0) printf("\n");
        printf("%d\t", a[i]);
    }
}
