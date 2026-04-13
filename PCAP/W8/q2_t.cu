#include <stdio.h>
#include <string.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void rowCalc(int *A, int *B, int *R, int m1, int n1, int m2, int n2){
	int row = blockIdx.x*blockDim.x + threadIdx.x;

	if(row<m1){
		for(int j=0;j<n2;j++){
			int sum=0;
			for(int i=0;i<n1;i++){
				sum+= A[row*n1+i]*B[i*n2+j];
			}
		R[row*n2+j] = sum;
		}
	}
}	

__global__ void colCalc(int *A, int *B, int *R, int m1, int n1, int m2, int n2){
	int col = blockIdx.x*blockDim.x + threadIdx.x;

	if(col<n2){
		for(int j=0;j<m1;j++){
			int sum=0;
			for(int i=0;i<n1;i++){
				sum+= A[j*n1+i]*B[i*n2+col];
			}
		R[j*n2+col] = sum;
		}
	}
}

__global__ void indiCalc(int *A, int *B, int *R, int m1, int n1, int m2, int n2){
	int row = blockIdx.x*blockDim.x + threadIdx.x;
	int col = blockIdx.x;

	if(col<n2 && row<m1){
		R[row*n2+col]=0;
		for(int i=0;i<n1;i++)
			R[row*n2+col] += A[row*n1+i]*B[i*n2+col];
		}
	}

int main(){
	int *A, *B, *R;
	int *d_a, *d_b, *d_r;
	int m1,n1, m2, n2;

	
	printf("for A\n");
	printf("emter dim\n");
	scanf("%d%d", &m1,&n1);
	int size1 = m1*n1*sizeof(int);
	A = (int *) malloc(size1);
	printf("enter A\n");
	for(int i=0;i<m1*n1;i++){
			scanf("%d", &A[i]);
	}
	

	printf("for B\n");
	printf("emter dim\n");
	scanf("%d%d", &m2,&n2);
	int size2 = m2*n2*sizeof(int);
	B = (int *)malloc(size2);

	printf("enter B\n");
	for(int i=0;i<m2*n2;i++){
			scanf("%d", &B[i]);
	}
	
	R = (int *)malloc(m1*n2*sizeof(int));
	cudaMalloc(&d_a, size1);
	cudaMalloc(&d_b, size2);
	cudaMalloc(&d_r, m1*n2*sizeof(int));

	cudaMemcpy(d_a, A, size1, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, B, size2, cudaMemcpyHostToDevice);


	// for row calc
	printf("for row wise calculation\n");
	dim3 grid1(1,1,1);
	dim3 block1(m1,1,1);

	rowCalc<<<grid1, block1>>>(d_a, d_b, d_r, m1,n1, m2, n2);

	cudaMemcpy(R, d_r, m1*n2*sizeof(int), cudaMemcpyDeviceToHost);
	printf("final R\n");
	for(int i=0;i<m1*n2;i++){
		if(i%n2 == 0) printf("\n");
			printf("%d\t", R[i]);
	}
	printf("\n----------------------------------------------------------------\n");

	// for col calc
	printf("for col wise calculation\n");
	dim3 grid2(1,1,1);
	dim3 block2(n2,1,1);

	colCalc<<<grid2, block2>>>(d_a, d_b, d_r, m1,n1, m2, n2);

	cudaMemcpy(R, d_r, m1*n2*sizeof(int), cudaMemcpyDeviceToHost);
	printf("final R\n");
	for(int i=0;i<m1*n2;i++){
		if(i%n2 == 0) printf("\n");
			printf("%d\t", R[i]);
	}
	printf("\n----------------------------------------------------------------\n");

	// for indi calc
	printf("for individual calculation\n");
	dim3 grid3(1,1,1);
	dim3 block3(m1*n2,1,1);

	indiCalc<<<grid3, block3>>>(d_a, d_b, d_r, m1,n1, m2, n2);

	cudaMemcpy(R, d_r, m1*n2*sizeof(int), cudaMemcpyDeviceToHost);
	printf("final R\n");
	for(int i=0;i<m1*n2;i++){
		if(i%n2 == 0) printf("\n");
			printf("%d\t", R[i]);
	}
	printf("\n----------------------------------------------------------------\n");
}
