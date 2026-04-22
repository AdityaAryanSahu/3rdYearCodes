#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#define tile_width 2


__global__ void calc(int *a, int *b, int *out, int n ){
    __shared__ int mds[tile_width][tile_width];
    __shared__ int nds[tile_width][tile_width];

    int bx = blockIdx.x; int by = blockIdx.y;
    int tx= threadIdx.x; int ty = threadIdx.y;

    int row = by*tile_width+ty;
    int col = bx*tile_width+tx;
 
    int val=0;
    for(int i=0;i< (n + tile_width - 1)/tile_width;i++){
        mds[ty][tx] = a[row*n+ i*tile_width+tx];
        nds[ty][tx] = b[(i*tile_width+ty)*n+col];
    
    __syncthreads();
    
    for(int i=0;i<tile_width;i++){
        val+= mds[ty][i]*nds[i][tx];
        }

        __syncthreads();
    }

    if(row < n && col < n)
    out[row*n+col]=val;
}


int main(){
    printf("enter dim n\n");
    int n;
    scanf("%d", &n);

    int a[n*n], b[n*n], out[n*n];
    int *d_a, *d_b,*d_out;
    int size = sizeof(int)*n*n;

    printf("enter a\n");
    for(int i=0;i<n*n;i++){
        scanf("%d", &a[i]);
    }

     printf("enter b\n");
    for(int i=0;i<n*n;i++){
        scanf("%d", &b[i]);
    }

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_out, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    dim3 grid(ceil(n/2.0), ceil(n/2.0),1);
    dim3 block(2,2,1);

    calc<<<grid, block>>>(d_a, d_b, d_out, n);
    cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);

    for(int i=0;i<n*n;i++){
        if(i%n == 0) printf("\n");
        printf("%d\t", out[i]);
    }

}