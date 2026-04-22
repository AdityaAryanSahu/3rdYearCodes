#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void calc(char*a, int *b, char *out, int m, int n){
    int row = threadIdx.x;
    int col = threadIdx.y;
    if(col<n && row<m){
        int idx = row * n + col;
        int rep = b[idx];
        char c = a[idx];

        int place = 0;
        for(int i=0;i<idx;i++){
                place+=b[i];
        }
        printf("%d%c\t", place,c);
            for(int i=0;i<rep;i++){
            out[place+i]=c;
        }
    }
}


int main(){
    int m,n;
    printf("enter dim m x n\n");
    scanf("%d%d", &m,&n);

    int b[m*n];
    char a[m*n+1];

    printf("enter array a\n");
    for(int i=0;i<m*n;i++) scanf(" %c", &a[i]);
    a[m*n]='\0';
    printf("enter array b\n");
    for(int i=0;i<m*n;i++) scanf("%d", &b[i]);
    puts(a);
    int size3=0;
    for(int i=0;i<m*n;i++) size3+=b[i];
    char out[size3+1];

    int size1 = m*n*sizeof(int);
    int size2 = m*n*sizeof(char);
    char *d_a, *d_out;
    int *d_b;
    cudaMalloc((void**)&d_a, size2);
    cudaMalloc((void**)&d_b, size1);
    cudaMalloc((void**)&d_out, size3*sizeof(char));

    cudaMemcpy(d_a, a, size2, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size1, cudaMemcpyHostToDevice);

    dim3 grid(1,1,1);
    dim3 block(m,n,1);
    calc<<<grid, block>>>(d_a, d_b, d_out, m,n);
     cudaMemcpy(out, d_out, size3*sizeof(char), cudaMemcpyDeviceToHost);
    out[size3]='\0';
     printf("final string\n");
     puts(out);
}