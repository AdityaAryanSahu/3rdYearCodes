#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__device__ int complement(int num){
    if(num == 0) return 1;
    int sum=0;
    for(int i=0;num>0;i++){
        int bit = num%2;
        bit = (bit==0)? 1:0;
        sum=sum + (pow(10, i)*bit);
        num/=2;
    }
    return sum;
}

__global__ void calc(int *a,int *b,  int m, int n){
    int row = threadIdx.y;
    int col = threadIdx.x;
    if(row<m && col<n)
        if(row!=0 && row!=m-1 && col!=0 && col!=n-1){
            b[row*n+col]=complement(a[row*n+col]);
        }
        else b[row*n+col]=a[row*n+col];
}


int main(){
    int m,n;
    printf("enter dim m x n\n");
    scanf("%d%d", &m,&n);

    int a[m*n], b[m*n];
    printf("enter array a\n");
    for(int i=0;i<m*n;i++) scanf("%d", &a[i]);

    int size = m*n*sizeof(int);
    int *d_a, *d_b;
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);

    dim3 grid(1,1,1);
    dim3 block(n,m,1);
    calc<<<grid, block>>>(d_a, d_b, m,n);
    cudaMemcpy(b, d_b, size, cudaMemcpyDeviceToHost);

    for(int i=0;i<m*n;i++){
        if(i%n==0) printf("\n");
        printf("%d\t", b[i]);
    }
}