#include<mpi.h>
#include<stdio.h>


int fact(int n){

if(n==0 || n==1) return 1;
return fact(n-1)*n;

}

int fib(int n){
if(n==0) return 0;
if(n==1) return 1;

return fib(n-1)+fib(n-2);


}
int main(int argc, char *argv[]){

	int rank,res;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	
	if(rank%2==0){
	res=fact(rank);
	}
	else{
	res=fib(rank);
	}
	printf(" rank %d has the result %d\n", rank, res);
	
	
	MPI_Finalize();
	return 0;
}
