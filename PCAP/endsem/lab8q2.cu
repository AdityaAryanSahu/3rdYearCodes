#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void rowCalc(int *a, int *b, int *out, int ha, int wa, int hb, int wb){
    int row = threadIdx.x;
    if(row<ha){
        for(int i=0;i<wb;i++){
            int sum=0;
            for(int j=0;j<wa;j++)
                sum+= a[row*wa+j]*b[j*wb+i];
            out[row*wb+i] = sum;
        }
    }

}

__global__ void colCalc(int *a, int *b, int *out, int ha, int wa, int hb, int wb){
    int col = threadIdx.x;
    if(col<wb){
        for(int i=0;i<ha;i++){
            int sum=0;
            for(int j=0;j<wa;j++)
                sum+= a[i*wa+j]*b[j*wb+col];
            out[i*wb+col] = sum;
        }
    }

}

__global__ void indiCalc(int *a, int *b, int *out, int ha, int wa, int hb, int wb){
    int col = threadIdx.x;
    int row = threadIdx.y;

    if(row <ha && col<wb){
        out[row*wb+col]=0;
		for(int i=0;i<wa;i++)
			out[row*wb+col] += a[row*wa+i]*b[i*wb+col];
		}
    }



int main(){
    int m1,n1, m2, n2;
    printf("enter dim m1 x n1 and m2 x n2\n");
    scanf("%d%d%d%d", &m1,&n1, &m2, &n2);

    int a[m1*n1], b[m2*n2], out[m1*n2];

    printf("enter array a\n");
    for(int i=0;i<m1*n1;i++) scanf("%d", &a[i]);

    printf("enter array b\n");
    for(int i=0;i<m2*n2;i++) scanf("%d", &b[i]);

    int size1 = m1*n1*sizeof(int);
    int size2 = m2*n2*sizeof(int);
    int size3 = m1*n2*sizeof(int);
    int *d_a, *d_b, *d_out;
    cudaMalloc((void**)&d_a, size1);
    cudaMalloc((void**)&d_b, size2);
    cudaMalloc((void**)&d_out, size3);

    cudaMemcpy(d_a, a, size1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size2, cudaMemcpyHostToDevice);

    printf("for row calc\n");

    dim3 grid1(1,1,1);
    dim3 block1(m1,1,1);
    
    rowCalc<<<grid1, block1>>>(d_a, d_b,d_out,  m1,n1, m2, n2);
    cudaMemcpy(out, d_out, size3, cudaMemcpyDeviceToHost);
    printf("final array\n");
    for(int i=0;i<m1*n2;i++) printf("%d\t", out[i]);
    printf("\n");

    printf("for col calc\n");

    dim3 grid2(1,1,1);
    dim3 block2(n2);
    
    colCalc<<<grid2, block2>>>(d_a, d_b, d_out, m1,n1, m2, n2);
    cudaMemcpy(out, d_out, size3, cudaMemcpyDeviceToHost);
    printf("final array\n");
    for(int i=0;i<m1*n2;i++) printf("%d\t", out[i]);
    printf("\n");

    printf("for indi calc\n");

    dim3 grid3(1,1,1);
    dim3 block3(n2,m1,1);
    
    indiCalc<<<grid3, block3>>>(d_a, d_b,d_out, m1,n1, m2, n2);
    cudaMemcpy(out, d_out, size3, cudaMemcpyDeviceToHost);

    printf("final array\n");
    for(int i=0;i<m1*n2;i++) printf("%d\t", out[i]);
    printf("\n");

}