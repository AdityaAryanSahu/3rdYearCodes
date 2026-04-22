#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void rowCalc(int *a, int *b, int *out, int height, int width){
    int row = threadIdx.x;
    if(row<height){
        for(int i=0;i<width;i++){
            out[row*width+i] = a[row*width+i]+b[row*width+i];
        }
    }

}

__global__ void colCalc(int *a, int *b, int *out, int height, int width){
    int col = threadIdx.x;
    if(col<width){
        for(int i=0;i<height;i++){
            out[col*height+i] = a[col*height+i]+b[col*height+i];
        }
    }

}

__global__ void indiCalc(int *a, int *b, int *out, int height, int width){
    int col = threadIdx.x;
    int row = threadIdx.y;

    if(row <height && col<width){
       
           out[row*width+col] = a[row*width+col]+b[row*width+col];
    }

}


int main(){
    int m,n;
    printf("enter dim m x n\n");
    scanf("%d%d", &m,&n);

    int a[m*n], b[m*n], out[m*n];

    printf("enter array a\n");
    for(int i=0;i<m*n;i++) scanf("%d", &a[i]);

    printf("enter array b\n");
    for(int i=0;i<m*n;i++) scanf("%d", &b[i]);

    int size = m*n*sizeof(int);
    int *d_a, *d_b, *d_out;
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_out, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    printf("for row calc\n");

    dim3 grid1(1,1,1);
    dim3 block1(m,1,1);
    
    rowCalc<<<grid1, block1>>>(d_a, d_b,d_out,  m,n);
    cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);
    printf("final array\n");
    for(int i=0;i<m*n;i++) printf("%d\t", out[i]);
    printf("\n");

    printf("for col calc\n");

    dim3 grid2(1,1,1);
    dim3 block2(n);
    
    rowCalc<<<grid2, block2>>>(d_a, d_b, d_out, m,n);
    cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);
    printf("final array\n");
    for(int i=0;i<m*n;i++) printf("%d\t", out[i]);
    printf("\n");

    printf("for indi calc\n");

    dim3 grid3(1,1,1);
    dim3 block3(n,m,1);
    
    rowCalc<<<grid3, block3>>>(d_a, d_b,d_out, m,n);
    cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);

    printf("final array\n");
    for(int i=0;i<m*n;i++) printf("%d\t", out[i]);
    printf("\n");

}