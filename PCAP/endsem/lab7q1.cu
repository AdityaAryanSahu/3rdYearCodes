#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void countWords(char *s, char*w, int *len, int n, int m, int words, int *count){
    int i = blockDim.x*blockIdx.x+threadIdx.x;

    if(i<words){
    int pos=0;
    int flag=1;
        for(int j=0;j<i;j++) pos+=len[j]+1;
        for(int j=0;j<m;j++) {if(s[pos+j]!=w[j]){ flag=0;break;}}
        if(flag && len[i]==m) atomicAdd(count,1);
    }
}

int main(){
    char s[1000], w[100];
    printf("enter sentance\n");
    fgets(s, sizeof(s), stdin);

    printf("word to be searched\n");
    scanf("%s", w);

    int size1 = sizeof(char)*strlen(s);
    int size2 = sizeof(char)*strlen(w);

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
    char *d_s, *d_w;
    int *d_len, *d_count;

    cudaMalloc((void**)&d_s, size1);
    cudaMalloc((void**)&d_w, size2);
    cudaMalloc((void**)&d_len, sizeof(int)*words);
    cudaMalloc((void**)&d_count, sizeof(int));


    cudaMemcpy(d_s, s, size1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_w, w, size2, cudaMemcpyHostToDevice);
    cudaMemcpy(d_len, len, words*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);
    dim3 grid(1,1,1);
    dim3 block(words, 1,1);

    countWords<<<grid, block>>>(d_s, d_w, d_len, strlen(s), strlen(w), words, d_count);
    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("total count: %d\n", count);



}