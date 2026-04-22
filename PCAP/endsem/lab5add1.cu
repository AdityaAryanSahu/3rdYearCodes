#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void eqn(int *x, int *y, int a, int n){
    int i= blockDim.x*blockIdx.x+threadIdx.x;

    if(i<n){
        y[i] = a*x[i]+y[i];
    }
}

int main(){
    printf("enter n\n");
    int n;
    scanf("%d",&n);
    int x[n], y[n];
    printf("enter array x\n");
    for(int i=0;i<n;i++) scanf("%d", &x[i]);

    printf("enter array y\n");
    for(int i=0;i<n;i++) scanf("%d", &y[i]);

    printf("enter alpha\n");
    int a;
    scanf("%d", &a);

    int *d_x, *d_y;
    int size = sizeof(int)*n;

    cudaMalloc((void**)&d_x, size);
    cudaMalloc((void**)&d_y, size);

    cudaMemcpy(d_x, x, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, size, cudaMemcpyHostToDevice);
    dim3 grid(1,1,1);
	dim3 block(n,1,1);
    eqn<<<grid, block>>>(d_x,d_y, a, n);
    cudaMemcpy(y , d_y , size, cudaMemcpyDeviceToHost);

    printf("final ans\n");
    for(int i=0;i<n;i++) printf("%d\t", y[i]);
}