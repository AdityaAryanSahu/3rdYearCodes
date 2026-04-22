#include<stdio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void copy(char *s, char* out, int m, int n){
    int id = blockIdx.x*blockDim.x+threadIdx.x;

    if(id<m){
        char c = s[id];
        int pos=id;
        for(int i=0;i<n;i++){
            out[pos]=c;
            pos+=m;
        }
    }
}

int main(){
    char s[1000], rs[1000];
    printf("enter sentance\n");
    scanf("%s", s);
    int n;
    printf("enter n\n");
    scanf("%d",&n);
    char*d_s, *d_rs;
    cudaMalloc(&d_s, strlen(s));
	int rs_size=n*strlen(s);

	cudaMalloc(&d_rs, rs_size);
	cudaMemcpy(d_s, s, strlen(s), cudaMemcpyHostToDevice);
	dim3 grid(1,1,1);
	dim3 block(strlen(s),1,1);
	copy<<<grid, block>>>(d_s, d_rs, strlen(s), n);
	cudaMemcpy(rs, d_rs, rs_size, cudaMemcpyDeviceToHost);
	rs[rs_size]='\0';
	printf("RS: ");
	puts(rs);

}