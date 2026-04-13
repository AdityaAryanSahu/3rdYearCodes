#include <stdio.h>
#include <math.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void calc(int *A, int m, int n){
	int row = blockIdx.x*blockDim.x + threadIdx.x;

	if(row < m){
		for(int i=0;i<n;i++){
			A[row*n+i] = pow(A[row*n+i], row+1);
		}
	}
    
}	


int main(){
	int *A;
	int *d_a;
	int m,n;
	printf("emter dim\n");
	scanf("%d%d", &m,&n);
	int size = m*n*sizeof(int);
	A = (int *) malloc(size);
	

	printf("enter A\n");
	for(int i=0;i<m*n;i++){
			scanf("%d", &A[i]);
	}

	cudaMalloc(&d_a, size);
	
	cudaMemcpy(d_a, A, size, cudaMemcpyHostToDevice);

	dim3 grid(1,1,1);
	dim3 block(m,1,1);

    calc<<<grid, block>>>(d_a, m,n);

	cudaMemcpy(A, d_a, size, cudaMemcpyDeviceToHost);

	printf("final matrix\n");
	for(int i=0;i<m*n;i++){
		if(i%n == 0) printf("\n");
			printf("%d\t", A[i]);
	}
    printf("\n");
	
}
