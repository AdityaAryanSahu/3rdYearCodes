#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void even_odd(int *A, int n){
	int id = blockIdx.x * blockDim.x+threadIdx.x;
	int t;
	if(id % 2 !=0 && id < n-1){
		if(A[id]> A[id+1]){
			t = A[id];
			A[id]=A[id+1];
			A[id+1]=t;
		}
	}

}

__global__ void odd_even(int *A, int n){
	int id = blockIdx.x * blockDim.x+threadIdx.x;
	int t;
	if(id % 2 ==0 && id < n-1){
		if(A[id]> A[id+1]){
			t = A[id];
			A[id]=A[id+1];
			A[id+1]=t;
		}
	}

}

int main(){
	int n;
    printf("enter n\n");
    scanf("%d", &n);
   
	int a1[n], res[n];
	printf("enter array\n");
	for(int i=0;i<n;i++) scanf("%d", &a1[i]);
	
	
	int *c_a1;
	int size = sizeof(int)*n;
	
	cudaMalloc((void**) &c_a1, size);
	
	cudaMemcpy(c_a1 , a1, size, cudaMemcpyHostToDevice);
	
	
	dim3 gridsize1(ceil(n/256.0),1,1);
	dim3 blocksize1(256,1,1);

	for(int i=0;i<ceil(n/2.0);i++){
		even_odd<<<gridsize1, blocksize1>>>(c_a1, n);
		odd_even<<<gridsize1, blocksize1>>>(c_a1, n);
	}
	
	
	cudaMemcpy(res , c_a1 , size , cudaMemcpyDeviceToHost);


	for(int i=0;i<n;i++){
		printf("%d\t", res[i]);
	}
	printf("\n");


}