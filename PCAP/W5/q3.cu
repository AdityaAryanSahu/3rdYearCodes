#define _USE_MATH_DEFINES
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<math.h>

__global__ void covert(double *A, double *B, int n){

	int id = blockIdx.x * blockDim.x+threadIdx.x;
	if(id<n)
	B[id] = sinf(A[id]);
	
}


int main(){
    int n;
    printf("enter n\n");
    scanf("%d", &n);
   
	double a1[n], a2[n];
	printf("enter angles\n");
	for(int i=0;i<n;i++) scanf("%lf", &a1[i]);
	
	
	for(int i=0;i<n;i++) a1[i] = a1[i] * M_PI / 180.0;
	
	
	double *c_a1, *c_a2;
	int size = sizeof(double)*n;
	
	cudaMalloc((void**) &c_a1, n*sizeof(double));
	cudaMalloc((void**) &c_a2, n*sizeof(double));
	
	cudaMemcpy(c_a1 , a1, size, cudaMemcpyHostToDevice);
	
	dim3 gridsize1(n,1,1);
	dim3 blocksize1(1,1,1);
	
	covert<<<gridsize1, blocksize1>>>(c_a1,c_a2, n);
	cudaMemcpy(a2 , c_a2 , size, cudaMemcpyDeviceToHost);
	
	printf("result\n");
	for(int i=0;i<n;i++){
	
		printf("%.2f\t", a2[i]);
	}
	printf("\n");
}
