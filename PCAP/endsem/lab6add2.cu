#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void convert(int *data, int *out, int n){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i<n){
        int num = data[i];
        int sum=0;
        int place =1;
        while(num > 0){
            int bit = num % 10;
            bit = (bit == 0) ? 1 : 0;
            sum += place * bit;
            place *= 10;
            num /= 10;
        }
        out[i]=sum;
    }
} 


int main(){
    printf("enter n\n");
    int n;
    scanf("%d", &n);

    int data[n], out[n];

    printf("enter data\n");
    for(int i=0;i<n;i++) scanf("%d", &data[i]);

    int *d_data,*d_out;
    int size= sizeof(int)*n;

    cudaMalloc((void**)&d_data, size);
    cudaMalloc((void**)&d_out, size);
    cudaMemcpy(d_data, data, size,cudaMemcpyHostToDevice);
    dim3 grid(1,1,1);
    dim3 block(n,1,1);

    convert<<<grid, block>>>(d_data,d_out ,n);
    cudaMemcpy(out, d_out, size,cudaMemcpyDeviceToHost);

    printf("final array\n");
    for(int i=0;i<n;i++) printf("%d\t", out[i]);



}