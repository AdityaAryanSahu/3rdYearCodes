#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<math.h>

__global__ void selectionsort(int *A, int *ans,int n)
{
	int tid=blockIdx.x*blockDim.x + threadIdx.x;
	if(tid>=n)
		return;
	
	int pos=0;
	
	int data=A[tid];
	for(int i=0;i<n;i++)
	{
		if(A[i]<data || (A[i]==data && i<tid) )
			pos++;
	}
	ans[pos]=data;
}

int main()
{
	int n;
	printf("Enter value of n: ");
	scanf("%d",&n);
	int a[n],ans[n];
	
	int *d_a,*d_b;
	int sz=sizeof(int)*n;
	
	cudaMalloc((void **)&d_a, sz);
	cudaMalloc((void **)&d_b, sz);
	
	
	
	printf("Enter elemenets: ");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	
	cudaMemcpy(d_a,a,sz,cudaMemcpyHostToDevice);
	
	dim3 gridsize(ceil(n/256.0),1,1);
	dim3 blocksize(256,1,1);
	
	selectionsort<<<gridsize,blocksize>>>(d_a,d_b,n);
	
	cudaMemcpy(ans,d_b,sz,cudaMemcpyDeviceToHost);
	
	printf("\nYour ans is: \n");
	for(int i=0;i<n;i++)
		printf("%d ",ans[i]);
	printf("\n");
	
}