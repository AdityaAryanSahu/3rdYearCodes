#include <stdio.h>
#include <string.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void rowCalc(int *A, int *B, int *R, int m, int n){
	int row = blockIdx.x*blockDim.x + threadIdx.x;

	if(row<m){
		for(int i=0;i<n;i++){
			R[row*n+i] = A[row*n+i]+B[row*n+i];
		}
	}
}	

__global__ void colCalc(int *A, int *B, int *R, int m, int n){
	int col = blockIdx.x*blockDim.x + threadIdx.x;

	if(col<n){
		for(int i=0;i<m;i++){
			R[i*n+col] = A[i*n+col]+B[i*n+col];
		}
	}
}

__global__ void indiCalc(int *A, int *B, int *R, int m, int n){
	int row = blockIdx.x*blockDim.x + threadIdx.x;
	int col = blockIdx.x;

	if(col<n && row<m){
			R[row*n+col] = A[row*n+col]+B[row*n+col];
		}
	}

int main(){
	int *A, *B, *R;
	int *d_a, *d_b, *d_r;
	int m,n;
	printf("emter dim\n");
	scanf("%d%d", &m,&n);
	int size = m*n*sizeof(int);
	A = (int *) malloc(size);
	B = (int *)malloc(size);
	R = (int *)malloc(size);

	printf("enter A\n");
	for(int i=0;i<m*n;i++){
			scanf("%d", &A[i]);
	}

	printf("enter B\n");
	for(int i=0;i<m*n;i++){
			scanf("%d", &B[i]);
	}
	cudaMalloc(&d_a, size);
	cudaMalloc(&d_b, size);
	cudaMalloc(&d_r, size);

	cudaMemcpy(d_a, A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, B, size, cudaMemcpyHostToDevice);


	// for row calc
	printf("for row wise calculation\n");
	dim3 grid1(1,1,1);
	dim3 block1(m,1,1);

	rowCalc<<<grid1, block1>>>(d_a, d_b, d_r, m,n);

	cudaMemcpy(R, d_r, size, cudaMemcpyDeviceToHost);
	printf("final R\n");
	for(int i=0;i<m*n;i++){
		if(i%n == 0) printf("\n");
			printf("%d\t", R[i]);
	}
	printf("\n----------------------------------------------------------------\n");

	// for col calc
	printf("for col wise calculation\n");
	dim3 grid2(1,1,1);
	dim3 block2(n,1,1);

	colCalc<<<grid2, block2>>>(d_a, d_b, d_r, m,n);

	cudaMemcpy(R, d_r, size, cudaMemcpyDeviceToHost);
	printf("final R\n");
	for(int i=0;i<m*n;i++){
		if(i%n == 0) printf("\n");
			printf("%d\t", R[i]);
	}
	printf("\n----------------------------------------------------------------\n");

	// for indi calc
	printf("for individual calculation\n");
	dim3 grid3(1,1,1);
	dim3 block3(m*n,1,1);

	indiCalc<<<grid3, block3>>>(d_a, d_b, d_r, m,n);

	cudaMemcpy(R, d_r, size, cudaMemcpyDeviceToHost);
	printf("final R\n");
	for(int i=0;i<m*n;i++){
		if(i%n == 0) printf("\n");
			printf("%d\t", R[i]);
	}
	printf("\n----------------------------------------------------------------\n");

}

