#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void rowSum(int *a, int *out,int m, int n){
    int row = threadIdx.x;
    if(row<m){
        int sum=0;
        for(int i=0;i<n;i++){
            sum+=a[row*n+i];
        }
        out[row]=sum;
    }
}

__global__ void colSum(int *a, int *out,int m, int n){
    int col = threadIdx.x;
    if(col<n){
        int sum=0;
        for(int i=0;i<m;i++){
            sum+=a[i*n+col];
        }
        out[col]=sum;
    }
}

__global__ void calc(int *a, int *rowSum, int *colSum, int m, int n){
    int row = threadIdx.x;
    int col = threadIdx.y;

    if(row<m && col<n){
        a[row*n+col] = rowSum[row]+colSum[col];
    }
}


int main(){
    int m,n;
    printf("enter dim m x n\n");
    scanf("%d%d", &m,&n);


    int a[m*n];
    printf("enter array a\n");
    for(int i=0;i<m*n;i++) scanf("%d", &a[i]);

    int *d_a,*d_r, *d_c;

    cudaMalloc((void**)&d_a, sizeof(int)*m*n);
    cudaMalloc((void**)&d_r, sizeof(int)*m);
    cudaMalloc((void**)&d_c, sizeof(int)*n);

    cudaMemcpy(d_a, a, sizeof(int)*m*n, cudaMemcpyHostToDevice);

    dim3 grid(1,1,1);
    dim3 block1(m,1,1);
    rowSum<<<grid, block1>>>(d_a, d_r, m,n);

    dim3 block2(n,1,1);
    colSum<<<grid, block2>>>(d_a, d_c, m,n);

    dim3 block3(m,n,1);
    calc<<<grid, block3>>>(d_a, d_r,d_c,m,n);
    cudaMemcpy(a, d_a, sizeof(int)*m*n, cudaMemcpyDeviceToHost);

    for(int i=0;i<m*n;i++){
        if(i%n==0) printf("\n");
        printf("%d\t", a[i]);
    }
}