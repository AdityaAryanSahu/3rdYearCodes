#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>



__constant__ float d_mask[1024];

__global__ void tiledConv(float *input, float *output, int width, int mask_width,int tile_size) {
    extern __shared__ float tile[];

    int tx = threadIdx.x;
    int i = blockIdx.x * tile_size + tx;

    int halo = mask_width / 2;

   
    int sharedIndex = tx + halo;

    if (i < width)
        tile[sharedIndex] = input[i];

   
    if (tx < halo) {
        if (i - halo >= 0)
            tile[tx] = input[i - halo];
        else
            tile[tx] = 0;
    }

   
    if (tx >= (tile_size - halo)) {
        int rightHaloIndex = sharedIndex + halo;
        if (i + halo < width)
            tile[rightHaloIndex] = input[i + halo];
        else
            tile[rightHaloIndex] = 0.0f;
    }

    __syncthreads();

    if (i < width) {
        float sum = 0;
        for (int j = 0; j < mask_width; j++) {
            sum += tile[tx + j] * d_mask[j];
        }
        output[i] = sum;
    }
}

int main() {
    int width, mask_width, tile_size;
    printf("enter width, mask_width and tile size\n");
    scanf("%d%d%d", &width, &mask_width, &tile_size);

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

    int grid_dim = (width + tile_size - 1) / tile_size;
    dim3 gridsize(grid_dim, 1, 1);
    dim3 blocksize(tile_size, 1, 1);

    tiledConv<<<gridsize, blocksize, (tile_size + mask_width - 1)*sizeof(int)>>>(d_input, d_output, width, mask_width, tile_size);

    cudaMemcpy(output, d_output, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Output:\n");
    for (int i = 0; i < width; i++)
        printf("%.2f\t ", output[i]);

    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}