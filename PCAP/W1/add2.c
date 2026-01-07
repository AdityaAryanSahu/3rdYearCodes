#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include<unistd.h>

int isPrime(int n){
	for(int i=2;i<=sqrt(n);i++){
		if(n%i==0) return 0;
	}
	return 1;
}

int main(int argc, char *argv[]){

	int rank,res;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	for(int i=1;i<=100;i++){
		if(isPrime(i)) printf(" %d is prime as per rank %d\n", i, rank);
		else printf(" %d is not prime as per rank %d\n", i, rank);
		sleep(2);
	}
	
	
	MPI_Finalize();
	return 0;
}
