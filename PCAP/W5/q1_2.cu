#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>


__global__ void vecAdd(int *A, int *B, int * C, int n){

	int id = blockIdx.x * blockDim.x+threadIdx.x;
	if(id<n)
	C[id] = A[id]+B[id];
}


int main(){
    int n;
    printf("enter n\n");
    scanf("%d", &n);
   
	int a1[n], a2[n], a3[n];
	printf("enter array1\n");
	for(int i=0;i<n;i++) scanf("%d", &a1[i]);
	
	printf("enter array2\n");
	for(int i=0;i<n;i++) scanf("%d", &a2[i]);
	
	int *c_a1, *c_a2, *c_a3;
	int size = sizeof(int)*n;
	
	cudaMalloc((void**) &c_a1, n*sizeof(int));
	cudaMalloc((void**) &c_a2, n*sizeof(int));
	cudaMalloc((void**) &c_a3, n*sizeof(int));
	
	cudaMemcpy(c_a1 , a1, size, cudaMemcpyHostToDevice);
	cudaMemcpy(c_a2 , a2 , size, cudaMemcpyHostToDevice);
	
	dim3 gridsize1(n,1,1);
	dim3 blocksize1(1,1,1);
	
	vecAdd<<<gridsize1, blocksize1>>>(c_a1,c_a2,c_a3, n);
	cudaMemcpy(a3 , c_a3 , size , cudaMemcpyDeviceToHost);
	
	printf("q1 a:\n");
	for(int i=0;i<n;i++){
	
		printf("%d\t", a3[i]);
	}
	printf("\n");
	
	printf("q1 b:\n");
	dim3 gridsize2(1,1,1);
	dim3 blocksize2(n,1,1);
	
	vecAdd<<<gridsize2, blocksize2>>>(c_a1,c_a2,c_a3, n);
	cudaMemcpy(a3 , c_a3 , size , cudaMemcpyDeviceToHost);
	
	
	for(int i=0;i<n;i++){
	
		printf("%d\t", a3[i]);
	}
	printf("\n");
	
	printf("q2:\n");
	dim3 gridsize3(ceil(n/256.0),1,1);
	dim3 blocksize3(256,1,1);
	
	vecAdd<<<gridsize3, blocksize3>>>(c_a1,c_a2,c_a3, n);
	cudaMemcpy(a3 , c_a3 , size , cudaMemcpyDeviceToHost);
	
	
	for(int i=0;i<n;i++){
	
		printf("%d\t", a3[i]);
	}
	printf("\n");
	return 0;
	
	


}



