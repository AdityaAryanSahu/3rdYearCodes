#include <stdio.h>
#include <string.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__device__ int comple(int num){
    if(num == 0) return 1;
    int sum=0;
    for(int i=0;num>0;i++){
        int bit = num%2;
        bit = (bit == 0)? 1:0;
        sum=sum+(pow(10,i)*bit);
        num/=2;
    }
    return sum;
}

__global__ void calc(int *A, int *B, int m, int n){
	int row = (blockIdx.x*blockDim.x + threadIdx.x)/n;
    int col = (blockIdx.x*blockDim.x + threadIdx.x)% n;

	if(row !=0 && row != m-1 && col != 0 && col != n-1){
        B[row*n+col] = comple(A[row*n+col]);
    }
    else B[row*n+col] = A[row*n+col];
}	


int main(){
	int *A,*B;
	int *d_a, *d_b;
	int m,n;
	printf("emter dim\n");
	scanf("%d%d", &m,&n);
	int size = m*n*sizeof(int);
	A = (int *) malloc(size);
    B = (int *) malloc(size);
	

	printf("enter A\n");
	for(int i=0;i<m*n;i++){
			scanf("%d", &A[i]);
	}

	cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
	
	cudaMemcpy(d_a, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, B, size, cudaMemcpyHostToDevice);

	dim3 grid(1,1,1);
	dim3 block(m*n,1,1);

    calc<<<grid, block>>>(d_a, d_b,m,n);

	cudaMemcpy(B, d_b, size, cudaMemcpyDeviceToHost);

	printf("final matrix\n");
	for(int i=0;i<m*n;i++){
		if(i%n == 0) printf("\n");
			printf("%d\t", B[i]);
	}
    printf("\n");
	
}
