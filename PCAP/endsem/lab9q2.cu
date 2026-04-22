#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void calc(int *a, int m, int n){
    int row = threadIdx.x;
    if(row<m)
    for(int i=0;i<n;i++){
        int num=a[row*n+i];
        a[row*n+i]= pow(num, (row+1));
    }
}


int main(){
    int m,n;
    printf("enter dim m x n\n");
    scanf("%d%d", &m,&n);

    int a[m*n];
    printf("enter array a\n");
    for(int i=0;i<m*n;i++) scanf("%d", &a[i]);

    int size = m*n*sizeof(int);
    int *d_a;
    cudaMalloc((void**)&d_a, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    dim3 grid(1,1,1);
    dim3 block(m,1,1);
    calc<<<grid, block>>>(d_a, m,n);
    cudaMemcpy(a, d_a, size, cudaMemcpyDeviceToHost);

    for(int i=0;i<m*n;i++){
        if(i%n==0) printf("\n");
        printf("%d\t", a[i]);
    }
}