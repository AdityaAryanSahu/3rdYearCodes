#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#define mask_width 3

__constant__ int d_mask[mask_width];

__global__ void conv(int *data, int *out, int width){
    int i= blockIdx.x*blockDim.x+threadIdx.x;
    if(i<width){
    int start=i-mask_width/2;
    int sum=0;
    for(int j=0;j<mask_width;j++){
        if(start+j>=0 && start+j<width)
            sum+= data[start+j]*d_mask[j];
    }
    out[i] = sum;
}
}

int main(){
    int width;
    printf("enter width\n");
    scanf("%d", &width);

    int data[width], mask[mask_width], out[width];
    printf("enter data\n");
    for(int i=0;i<width;i++) scanf("%d", &data[i]);

    printf("enter mask\n");
    for(int i=0;i<mask_width;i++) scanf("%d", &mask[i]);

    int *d_data, *d_out;
    int size1 = sizeof(int)*width;
    int size2 = sizeof(int)*mask_width;
    cudaMalloc((void**)&d_data, size1);
    cudaMalloc((void**)&d_out, size1);

    cudaMemcpy(d_data, data, size1, cudaMemcpyHostToDevice);
    cudaMemcpyToSymbol(d_mask, mask, size2);

    dim3 grid(1,1,1);
    dim3 block(width,1,1);
    conv<<<grid, block>>>(d_data, d_out, width);
    cudaMemcpy(out, d_out, size1, cudaMemcpyDeviceToHost);

    printf("final array\n");
    for(int i=0;i<width;i++) printf("%d\t", out[i]);

}