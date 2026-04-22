#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#define tile_width 2
#define mask_width 3

__constant__ int d_mask[mask_width];
__global__ void calc(int *data, int *out, int width){
    __shared__ int tile[tile_width];
    int tx = threadIdx.x;
    int idx = blockIdx.x*tile_width+tx;

    int halo= mask_width/2;

    int sharedIndex = tx+halo;

    if(idx<width) tile[sharedIndex] = data[idx];

    if(tx<halo){
        if(idx-halo>=0) tile[tx] = data[idx-halo];
        else tile[tx]=0;
    }

    if(tx>= (tile_width-halo)){
        int right = sharedIndex+halo;
        if(idx+halo <width) tile[right] = data[idx+halo];
        else tile[right]=0;
    }
    __syncthreads();

    if(idx<width){
        int sum=0;
        for(int i=0;i<mask_width;i++)
            sum+=tile[tx+i]*d_mask[i];

        out[idx]=sum;
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

    int griddim = (width +tile_width-1)/tile_width;

    dim3 grid(griddim, 1, 1);
    dim3 block(tile_width, 1,1);

    calc<<<grid, block>>>(d_data, d_out, width);
    cudaMemcpy(out, d_out, size1, cudaMemcpyDeviceToHost);

    printf("final array\n");
    for(int i=0;i<width;i++) printf("%d\t", out[i]);
}