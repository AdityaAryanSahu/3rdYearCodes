#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void convert(int *data, int *out, int n){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i<n){
        int num = data[i];
        int sum=0;
        for(int j=0;num>0;j++){
            int bit = num%8;
            sum=sum+(pow(10,j)*bit);
            num/=8;
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