#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void add(int *a, int *b, int *c, int n){
    int i= blockIdx.x*blockDim.x+threadIdx.x;
    if(i<n)
        c[i] = a[i]+b[i];
}

int main(){
    printf("enter dim\n");
    int n;
    scanf("%d", &n);
    int a[n], b[n], c[n];
    int *d_a, *d_b, *d_c;

    printf("enter array a\n");
    for(int i=0;i<n;i++) scanf("%d", &a[i]);

    printf("enter array b\n");
    for(int i=0;i<n;i++) scanf("%d", &b[i]);

    int size = sizeof(int)*n;

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    dim3 grid(n, 1,1);
    dim3 block(1,1, 1);

    add<<<grid, block>>>(d_a, d_b, d_c, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf("array c\n");
    for(int i=0;i<n;i++) printf("%d\t", c[i]);

    printf("\n");
    dim3 grid1(1, 1,1);
    dim3 block1(n,1, 1);

    add<<<grid1, block1>>>(d_a, d_b, d_c, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf("array c\n");
    for(int i=0;i<n;i++) printf("%d\t", c[i]);

}