#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void copy(char *s, char* out, int m){
    int id = blockIdx.x*blockDim.x+threadIdx.x;

    if(id<m){
        char c = s[id];
        int start = (id * (id + 1)) / 2; 
        for(int i=0;i<=id;i++){
            out[i+start]=c;
          
        }
    }
}

int main(){
    char s[1000], rs[1000];
    printf("enter sentance\n");
    scanf("%s", s);
    char*d_s, *d_rs;
    int len=strlen(s);
    cudaMalloc(&d_s, len);

	int rs_size=(len* (len+1))/2;
	cudaMalloc(&d_rs, rs_size);
	cudaMemcpy(d_s, s, len, cudaMemcpyHostToDevice);
	dim3 grid(1,1,1);
	dim3 block(len,1,1);
	copy<<<grid, block>>>(d_s, d_rs, len);
	cudaMemcpy(rs, d_rs, rs_size, cudaMemcpyDeviceToHost);
	rs[rs_size]='\0';
	printf("RS: ");
	puts(rs);

}