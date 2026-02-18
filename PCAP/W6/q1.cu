#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void conv1D(float *N, float *M, float *P,int width, int mask_width){
	int id = blockIdx.x * blockDim.x+threadIdx.x;
	int start = id - mask_width/2;
	float val=0;
	for(int i=0;i<mask_width;i++){
		if(start+i >=0 && start+i<width)
			val+=N[start+i]*M[i];
	}
	P[id] = val;

}



int main(){
	int width, mask_width;
    printf("enter width and mask_width\n");
    scanf("%d%d", &width, &mask_width);

 
	float a1[mask_width], a2[width], a3[width];
	printf("enter mask\n");
	for(int i=0;i<mask_width;i++) scanf("%f", &a1[i]);

	printf("enter array\n");
	for(int i=0;i<width;i++) scanf("%f", &a2[i]);
	
	

	
	float *m, *n, *p;
	int size = sizeof(float)*width;
	
	cudaMalloc((void**) &m, sizeof(float)* mask_width);
	cudaMalloc((void**) &n, size);
	cudaMalloc((void**) &p, size);
	
	cudaMemcpy(m , a1, sizeof(float)* mask_width, cudaMemcpyHostToDevice);
	cudaMemcpy(n , a2 , size, cudaMemcpyHostToDevice);
	
	
	dim3 gridsize1(ceil(width/256.0),1,1);
	dim3 blocksize1(256,1,1);

	conv1D<<<gridsize1, blocksize1>>>(n, m, p, width, mask_width);
	
	
	cudaMemcpy(a3 , p , size , cudaMemcpyDeviceToHost);


	for(int i=0;i<width;i++){
		printf("%.2f\t", a3[i]);
	}
	printf("\n");


}