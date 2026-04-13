#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>


__global__ void indiCalc(int *A, int *B, int *R, int m1, int n1, int m2, int n2){
	int row = blockIdx.y * blockDim.y + threadIdx.y; 
    int col = blockIdx.x * blockDim.x + threadIdx.x;

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
	
    if (n1 != m2) {
        printf("not possible\n");
        return 0;
    }


	R = (int *)malloc(m1*n2*sizeof(int));
	cudaMalloc(&d_a, size1);
	cudaMalloc(&d_b, size2);
	cudaMalloc(&d_r, m1*n2*sizeof(int));

	cudaMemcpy(d_a, A, size1, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, B, size2, cudaMemcpyHostToDevice);

    
    
    dim3 grid(ceil(n2/16.0), ceil(m1/16.0));
	dim3 block(16,16);
    

	indiCalc<<<grid, block>>>(d_a, d_b, d_r, m1,n1, m2, n2);

	cudaMemcpy(R, d_r, m1*n2*sizeof(int), cudaMemcpyDeviceToHost);
	printf("final R\n");
	for(int i=0;i<m1*n2;i++){
		if(i%n2 == 0) printf("\n");
			printf("%d\t", R[i]);
	}
}
