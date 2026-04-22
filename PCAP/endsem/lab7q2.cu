#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void copy(char *s, char* out, int m){
    int id = blockIdx.x*blockDim.x+threadIdx.x;
    if(id<m){
        int pos=0;
        for(int i=0;i<id;i++) pos+=m-i;
        for(int i=0;i<m-id;i++){
            out[pos+i] = s[i];
        }
    }
}

int main(){
    char s[1000], rs[1000];
    printf("enter sentance\n");
    fgets(s, sizeof(s), stdin);
    int n = strlen(s);
     if (s[n - 1] == '\n') {
        s[n - 1] = '\0';
        n--;  // Adjust the length to exclude the newline
    }
    char*d_s, *d_rs;
    cudaMalloc(&d_s, n);
	int rs_size=0;
	for(int i=0;i<n;i++) rs_size+= n-i;
	cudaMalloc(&d_rs, rs_size);
	cudaMemcpy(d_s, s, n, cudaMemcpyHostToDevice);
	dim3 grid(1,1,1);
	dim3 block(n,1,1);
	copy<<<grid, block>>>(d_s, d_rs, n);
	cudaMemcpy(rs, d_rs, rs_size, cudaMemcpyDeviceToHost);
	rs[rs_size]='\0';
	printf("RS: ");
	puts(rs);

}