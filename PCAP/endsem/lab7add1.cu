#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void countWords(char *s, int *len, int n, int words){
    int i = blockDim.x*blockIdx.x+threadIdx.x;

    if(i<words){
    int pos=0;
        for(int j=0;j<i;j++) pos+=len[j]+1;
        int m = len[i];
        for(int j=0;j<m/2;j++) {
            char t = s[pos+j];
            s[pos+j] = s[pos+m-j-1];
            s[pos+m-j-1]=t;
        }
    }
}

int main(){
    char s[1000];
    printf("enter sentance\n");
    fgets(s, sizeof(s), stdin);

    int size1 = sizeof(char)*strlen(s);
   

    int count=0;
    int len[100];
    int k=0;
    for(int i=0;i<strlen(s);i++){
        if(s[i] == ' ') {len[k++] = count; count =0; continue;}
        count++;
    }
    len[k]=count-1;
    int words = k+1;
    
    count=0;
    char *d_s;
    int *d_len, *d_count;

    cudaMalloc((void**)&d_s, size1);

    cudaMalloc((void**)&d_len, sizeof(int)*words);

    cudaMemcpy(d_s, s, size1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_len, len, words*sizeof(int), cudaMemcpyHostToDevice);

    dim3 grid(1,1,1);
    dim3 block(words, 1,1);

    countWords<<<grid, block>>>(d_s, d_len, strlen(s), words);
    cudaMemcpy(s, d_s, size1, cudaMemcpyDeviceToHost);

    puts(s);



}