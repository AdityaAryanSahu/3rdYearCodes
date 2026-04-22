#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// Kernel to compute row sums
__global__ void computeRowSum(int *a, int *rowSum, int m, int n){
    int row = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < m){
        int sum = 0;
        for(int j = 0; j < n; j++){
            sum += a[row * n + j];
        }
        rowSum[row] = sum;
    }
}

// Kernel to compute column sums
__global__ void computeColSum(int *a, int *colSum, int m, int n){
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(col < n){
        int sum = 0;
        for(int i = 0; i < m; i++){
            sum += a[i * n + col];
        }
        colSum[col] = sum;
    }
}

// Final kernel
__global__ void transform(int *a, int *out, int *rowSum, int *colSum, int m, int n){
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < m && col < n){
        int val = a[row * n + col];

        if(val % 2 == 0)
            out[row * n + col] = rowSum[row];
        else
            out[row * n + col] = colSum[col];
    }
}

int main(){
    int m, n;
    printf("Enter rows and cols:\n");
    scanf("%d %d", &m, &n);

    int a[m*n], out[m*n];

    printf("Enter matrix:\n");
    for(int i = 0; i < m*n; i++)
        scanf("%d", &a[i]);

    int *d_a, *d_out, *d_rowSum, *d_colSum;

    cudaMalloc((void**)&d_a, m*n*sizeof(int));
    cudaMalloc((void**)&d_out, m*n*sizeof(int));
    cudaMalloc((void**)&d_rowSum, m*sizeof(int));
    cudaMalloc((void**)&d_colSum, n*sizeof(int));

    cudaMemcpy(d_a, a, m*n*sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;

    // Row sum
    computeRowSum<<<(m+blockSize-1)/blockSize, blockSize>>>(d_a, d_rowSum, m, n);

    // Column sum
    computeColSum<<<(n+blockSize-1)/blockSize, blockSize>>>(d_a, d_colSum, m, n);

    cudaDeviceSynchronize();

    // 2D grid for final transformation
    dim3 block(16,16);
    dim3 grid((n+15)/16, (m+15)/16);

    transform<<<grid, block>>>(d_a, d_out, d_rowSum, d_colSum, m, n);

    cudaMemcpy(out, d_out, m*n*sizeof(int), cudaMemcpyDeviceToHost);

    printf("Output matrix:\n");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", out[i*n + j]);
        }
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_out);
    cudaFree(d_rowSum);
    cudaFree(d_colSum);

    return 0;
}