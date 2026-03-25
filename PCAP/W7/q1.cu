	#include <stdio.h>
	#include <string.h>
	#include "cuda_runtime.h"
	#include "device_launch_parameters.h"

	__global__ void countWords(char* s, char* w, int n, int m, int* count, int *len, int words){
		int id= blockIdx.x*blockDim.x+ threadIdx.x;
		if(id<words){
			int flag=1;
			int pos=0;
			for(int i=0;i<id;i++) pos+=len[i]+1;
			for(int i=0;i<m;i++) if(s[pos+i] != w[i]) {flag=0; break;}
			if(flag && len[id] == m) atomicAdd(count,1);
		}
	}

	int main(){
		char s[2000], w[50];
		int len[2000];
		char *d_s, *d_w;
		int *d_count,*d_length,  count = 0;

		printf("Enter sentence: ");
		fgets(s, sizeof(s), stdin);

		printf("Enter word to search: ");
		scanf("%s", w);
		int n = strlen(s);
		int m = strlen(w);
		int l=0;
		int idx=0;
		for(int i=0;i<n;i++){
			if(s[i]==' ') {
			len[idx]=l;
			l=0;
			idx++;
			}
			else l++;
		}
		len[idx]=l-1;
		int words = idx+1;
		
		cudaMalloc(&d_s, n);
		cudaMalloc(&d_w, m);
		cudaMalloc(&d_count, sizeof(int));
		cudaMalloc(&d_length, words*sizeof(int));

		cudaMemcpy(d_s, s, n, cudaMemcpyHostToDevice);
		cudaMemcpy(d_w, w, m, cudaMemcpyHostToDevice);
		cudaMemcpy(d_length, len, words*sizeof(int), cudaMemcpyHostToDevice);
		cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

		cudaEvent_t start, stop;
		cudaEventCreate(&start);
		cudaEventCreate(&stop);

		dim3 grid(1,1,1);
		dim3 block(words,1,1);
		cudaEventRecord(start,0);
		countWords<<<grid, block>>>(d_s, d_w, n, m, d_count, d_length, words);

		cudaEventRecord(stop,0);
		cudaEventSynchronize(stop);
		float time;
		cudaEventElapsedTime(&time, stop, 0);
		cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
		printf("Occurrences of '%s' = %d\n", w, count);
		printf("time taken: %f\n", time);

	}