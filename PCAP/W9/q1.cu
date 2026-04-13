#include <stdio.h>
#include <math.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void calc(int *data, int *X, int *Y, int *col_idx, int *row_ptr, int m){
	int row = blockIdx.x*blockDim.x + threadIdx.x;

	if(row<m){
		int dot=0;
		int start= row_ptr[row];
		int end=row_ptr[row+1];
		for(int ele=start;ele<end;ele++) 
			dot+=data[ele]*X[col_idx[ele]];
		Y[row]=dot;
	}
    
}	

int main(){
	
	int *A,*X,*row_ptr, *col_idx, *Y;
	int *d_a,*d_row_ptr, *d_col_idx, *d_x, *d_y;
	int m,n;
	printf("emter dim\n");
	scanf("%d%d", &m,&n);
	
	int data[m][n];
	int size = m*n*sizeof(int);
	A = (int *) malloc(size);
	X =(int *) malloc(sizeof(int)*n);
	Y =(int *) malloc(sizeof(int)*n);
	col_idx = (int *) malloc(size);
	row_ptr= (int *) malloc(m+1);
	row_ptr[0]=0;
	

	printf("enter data\n");
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			scanf("%d", &data[i][j]);
			}
	}
	
	printf("enter X\n");
	for(int i=0;i<n;i++){
			scanf("%d", &X[i]);
			}
	
	int k=0; //count of non zero elements in data
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
		if(!data[i][j]) continue;
		A[k]=data[i][j]; //A has all non zero ele after flattening
		col_idx[k++]=j; //keeps track of col indices of non zero ele
		}
		row_ptr[i+1] = k; //keeps track of row 
	}
	row_ptr[m] = k;
	
	printf("data in 1D flattened array: ");
	for(int i=0;i<k;i++) printf("%d\t", A[i]);
	
	printf("\ncol_idx: ");
	for(int i=0;i<k;i++) printf("%d\t", col_idx[i]);
	
	printf("\nrow_ptr: ");
	for(int i=0;i<=m;i++) printf("%d\t", row_ptr[i]);
	
	cudaMalloc(&d_a, k*sizeof(int));
	cudaMalloc(&d_col_idx, k*sizeof(int));
	cudaMalloc(&d_row_ptr, (m+1)*sizeof(int));
	cudaMalloc(&d_x, n*sizeof(int));
	cudaMalloc(&d_y, n*sizeof(int));
	
	cudaMemcpy(d_a, A, k*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_col_idx, col_idx, k*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_row_ptr, row_ptr, (m+1)*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_x, X, n*sizeof(int), cudaMemcpyHostToDevice);
	


	dim3 grid(1,1,1);
	dim3 block(m,1,1);

    calc<<<grid, block>>>(d_a,d_x,d_y,d_col_idx, d_row_ptr,m);

	cudaMemcpy(Y, d_y, n*sizeof(int), cudaMemcpyDeviceToHost);

	printf("\nfinal matrix");
	for(int i=0;i<m*1;i++){
		if(i%1 == 0) printf("\n");
			printf("%d\t", Y[i]);
	}
    printf("\n");
	
}
