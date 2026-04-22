#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#define max 1000

__global__ void comp(int *data, int *x, int *y, int *row_ptr, int *col_idx, int n){
    int row = threadIdx.x;
    if(row<n){
        int sum=0;
        int start = row_ptr[row];
        int end = row_ptr[row+1];

        for(int ele=start;ele<end;ele++){
            sum+= data[ele]*x[col_idx[ele]];
        }
        y[row]=sum;
    }
}

int main(){
    printf("enter dim n x n\n");
    int n;
    scanf("%d", &n);

    int data[n][n], x[n], y[n];
    int *d_fdata, *d_x,*d_y, *d_row_ptr, *d_col_idx;
    int fdata[max], row_ptr[max], col_idx[max];

    printf("enter original data array\n");
    for(int i=0;i<n;i++) 
        for(int j=0;j<n;j++)
            scanf(" %d",&data[i][j]);

    printf("enter original x array\n");
    for(int i=0;i<n;i++) scanf("%d",&x[i]);

    int k=0;
    row_ptr[0]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(!data[i][j]) continue;
            fdata[k] = data[i][j];
            col_idx[k++]=j;
        }
        row_ptr[i+1]=k;
    }

    printf("\nfaltenned data: ");
    for(int i=0;i<k;i++)
    printf("%d\t", fdata[i]);

    printf("\nrow_ptr: ");
    for(int i=0;i<=n;i++)
    printf("%d\t", row_ptr[i]);

    printf("\ncol_idx: ");
    for(int i=0;i<k;i++)
    printf("%d\t", col_idx[i]);

    printf("\n");

    cudaMalloc((void**)&d_fdata, sizeof(int)*k);
    cudaMalloc((void**)&d_col_idx, sizeof(int)*k);
    cudaMalloc((void**)&d_row_ptr, sizeof(int)*(n+1));
    cudaMalloc((void**)&d_x, sizeof(int)*n);
    cudaMalloc((void**)&d_y, sizeof(int)*n);

    cudaMemcpy(d_fdata, fdata, sizeof(int)*k, cudaMemcpyHostToDevice);
    cudaMemcpy(d_col_idx, col_idx, sizeof(int)*k, cudaMemcpyHostToDevice);
    cudaMemcpy(d_row_ptr, row_ptr, sizeof(int)*(n+1), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, sizeof(int)*n, cudaMemcpyHostToDevice);

    dim3 grid(1,1,1);
    dim3 block(n,1,1);

    comp<<<grid, block>>>(d_fdata, d_x,d_y,d_row_ptr, d_col_idx, n);
    cudaMemcpy(y, d_y, sizeof(int)*n, cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++){
        printf("%d\n", y[i]);
    }


}
