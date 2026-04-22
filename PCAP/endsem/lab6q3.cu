#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void even(int *data, int n){
    int i=blockDim.x*blockIdx.x+threadIdx.x;
    if(i< n-1 && i%2==0){
        if(data[i]>data[i+1]){
            int temp = data[i];
            data[i]=data[i+1];
            data[i+1]=temp;
        }
    }
}

__global__ void odd(int *data, int n){
    int i=blockDim.x*blockIdx.x+threadIdx.x;
    if(i< n-1 && i%2!=0){
        if(data[i]>data[i+1]){
            int temp = data[i];
            data[i]=data[i+1];
            data[i+1]=temp;
        }
    }
}

int main(){
    printf("enter n\n");
    int n;
    scanf("%d", &n);

    int data[n];

    printf("enter data\n");
    for(int i=0;i<n;i++) scanf("%d", &data[i]);

    int *d_data;
    int size= sizeof(int)*n;

    cudaMalloc((void**)&d_data, size);
    cudaMemcpy(d_data, data, size,cudaMemcpyHostToDevice);
    dim3 grid(1,1,1);
    dim3 block(n,1,1);

    for(int i=0;i<ceil(n/2.0);i++){
        odd<<<grid, block>>>(d_data,n);
        even<<<grid, block>>>(d_data,n);
    }
    cudaMemcpy(data, d_data, size,cudaMemcpyDeviceToHost);

    printf("final array\n");
    for(int i=0;i<n;i++) printf("%d\t", data[i]);

}