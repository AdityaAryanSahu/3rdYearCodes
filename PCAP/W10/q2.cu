#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__constant__ float d_mask[1024];

__global__ void conv1D(float *input, float *output, int width, int mask_width) {
    int id = blockIdx.x * blockDim.x+threadIdx.x;
	int start = id - mask_width/2;
	float val=0;
	for(int i=0;i<mask_width;i++){
		if(start+i >=0 && start+i<width)
			val+=input[start+i]*d_mask[i];
	}
	output[id] = val;
}

int main() {

    int width, mask_width;
    printf("enter width and mask_width\n");
    scanf("%d%d", &width, &mask_width);

    float mask[mask_width], input[width], output[width];

    printf("enter mask\n");
	for(int i=0;i<mask_width;i++) scanf("%f", &mask[i]);

	printf("enter array\n");
	for(int i=0;i<width;i++) scanf("%f", &input[i]);

    float *d_input, *d_output;

    cudaMalloc(&d_input, width * sizeof(float));
    cudaMalloc(&d_output, width * sizeof(float));

    cudaMemcpy(d_input, input, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpyToSymbol(d_mask, mask, mask_width * sizeof(float));

    dim3 gridsize(ceil(width/256.0),1,1);
	dim3 blocksize(256,1,1);

    conv1D<<<gridsize, blocksize>>>(d_input, d_output, width,mask_width);

    cudaMemcpy(output, d_output, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Output:\n");
    for (int i = 0; i < width; i++)
        printf("%.2f ", output[i]);

}